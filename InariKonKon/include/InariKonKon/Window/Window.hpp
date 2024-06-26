#pragma once

#include <string>

#include "InariKonKon/Window/Event/EventManager.hpp"
#include "InariKonKon/Graphics/Draw/RenderState.hpp"
#include "InariKonKon/Graphics/Draw/Drawable.hpp"
#include "InariKonKon/Window/Monitor.hpp"
#include "InariKonKon/Utility/Color.hpp"

struct GLFWwindow;

namespace ikk
{
	class Window final
	{
	public:
		struct Settings final
		{
			Monitor monitor;
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

		template<Dimension D, Projection P>
		void draw(const Drawable<D>& drawable, RenderState<D, P>& state = {}) const noexcept;
	private:
		std::uint32_t m_id;
		std::u8string m_title;
		Window::Settings m_settings;
		GLFWwindow* m_window;

		priv::EventManager m_eventManager{};

		GLFWwindow* const create(const std::u8string& title, const Monitor vm) const noexcept;
		void initWindowEvents() noexcept;

		friend class Application;
		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;
	};

	template<Dimension D, Projection P>
	void Window::draw(const Drawable<D>& drawable, RenderState<D, P>& state) const noexcept
	{
		this->setActive();
		gl->Enable(GL_DEPTH_TEST);
		if (!state.isTransparent)
		{
			switch (D)
			{
			case Dimension::_2D:
				gl->DepthFunc(GL_ALWAYS);
				drawable.draw(*this, state);
				break;
			case Dimension::_3D:
				gl->DepthFunc(GL_LESS);
				drawable.draw(*this, state);
				break;
			case Dimension::_GUI:
				gl->DepthFunc(GL_ALWAYS);
				gl->Enable(GL_BLEND);
				gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				drawable.draw(*this, state);
				gl->Disable(GL_BLEND);
				break;
			}
		}
	}
}