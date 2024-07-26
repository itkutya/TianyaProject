#pragma once

#include <string>

#include "InariKonKon/Graphics/RenderState/RenderState.hpp"
#include "InariKonKon/Graphics/Drawable/Drawable.hpp"
#include "InariKonKon/Window/Event/EventManager.hpp"
#include "InariKonKon/Transform/Transformable.hpp"
#include "InariKonKon/Window/Monitor.hpp"
#include "InariKonKon/Utility/Color.hpp"

struct GLFWwindow;

namespace ikk
{
	class Window final
	{
	public:
		typedef std::uint32_t WindowID;

		struct Settings final
		{
			vec2u size = { 0, 0 };
			std::uint32_t fpslimit = 0;
			bool vsync = true;
			bool fullscreen = false;
		};

		Window(const std::u8string& title, const Window::Settings settings);

		Window(const Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		[[nodiscard]] const bool shouldClose() const noexcept;

		void setActive(const bool active = true) const noexcept;

		void handleEvents() const noexcept;
		void clear(const Color clearColor) const noexcept;
		void render() const noexcept;

		[[nodiscard]] const std::uint32_t& getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool& isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::u8string& getTitle() const noexcept;
		void setTitle(const std::u8string& title) noexcept;

		[[nodiscard]] const float getAspectRatio() const noexcept;
		[[nodiscard]] const vec2u& getSize() const noexcept;
		void setSize(const vec2u size) noexcept;

		template<DrawableType T, Projection P = Projection::None>
		void draw(const T& drawable, const RenderState<P>& state = {}) const noexcept;
	private:
		WindowID m_id;
		std::u8string m_title;
		Window::Settings m_settings;
		Monitor m_monitor;
		GLFWwindow* m_window;

		priv::EventManager m_eventManager{};

		GLFWwindow* const create(const std::u8string& title, const Window::Settings settings) noexcept;
		void initWindowEvents() noexcept;

		friend class Application;
		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;
		friend class Keyboard;
		[[nodiscard]] const GLFWwindow* const getUnderlyingWindow() const noexcept;
		[[nodiscard]] GLFWwindow* const getUnderlyingWindow() noexcept;
	};

	template<DrawableType T, Projection P>
	void Window::draw(const T& drawable, const RenderState<P>& state) const noexcept
	{
		if (state.isTransparent == false)
		{
			this->setActive();
			gl->Enable(GL_DEPTH_TEST);
			gl->DepthFunc(GL_LESS);
			gl->Enable(GL_BLEND);
			gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			const Transform* transform = nullptr;
			if constexpr (
				std::is_base_of<Transformable<Dimension::_3D>, T>::value ||
				std::is_base_of<Transformable<Dimension::_2D>, T>::value ||
				std::is_base_of<Transformable<Dimension::_UI>, T>::value)
				transform = &drawable.getTransform();

			const FloatRect viewRect = { 0.f, 0.f, (float)this->getSize().x, (float)this->getSize().y };

			drawable.predraw(state, transform, viewRect);
			drawable.draw();
			drawable.postdraw(state);
		}
		//TODO:
		//else...
	}
}