#pragma once

#include <exception>
#include <print>
#include <string>
#include <queue>
#include <memory>

#include "InariKonKon/Window/Event/Manager/EventManager.hpp"

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Window/Event/Event.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"
#include "InariKonKon/Window/VideoMode.hpp"
#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Scene/Scene.hpp"

struct GLFWwindow;

namespace ikk
{
	class Window final
	{
	public:
		struct Settings
		{
			VideoMode videomode;
			std::uint32_t fpslimit	= 60;
			bool vsync				= false;
			bool fullscreem			= false;
		};

		Window(const std::string& title, const Window::Settings settings);

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

		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::string& getTitle() const noexcept;
		void setTitle(const std::string& title) noexcept;

		[[nodiscard]] const Vector2<std::uint32_t> getSize() const noexcept;
		void setSize(const Vector2<std::uint32_t> size) noexcept;

		[[nodiscard]] const float getAspectRatio() const noexcept;
		
		template<Draw::Dimension D, Projection P>
		void draw(const Drawable<D>& drawable, const RenderState<D, P>& state = {}) const noexcept;
		
		void draw(const Draw::Primitive type, const std::size_t count, const int offset = 0) const noexcept;
		void draw(const Draw::Primitive type, const std::size_t indiciesCount, const GLType eboType) const noexcept;
	private:
		std::uint32_t m_id;
		std::string m_title;
		Window::Settings m_settings;
		GLFWwindow* m_window;

		priv::EventManager m_eventManager{};

		GLFWwindow* const create(const std::string& title, const VideoMode vm) const noexcept;
		void initWindowEvents() noexcept;

		friend class Application;
		[[nodiscard]] const priv::EventManager& getEventManager() const noexcept;
		[[nodiscard]] priv::EventManager& getEventManager() noexcept;
	};

	template<Draw::Dimension D, Projection P>
	inline void Window::draw(const Drawable<D>& drawable, const RenderState<D, P>& state) const noexcept
	{
		this->setActive();
		switch (D)
		{
		case ikk::Draw::Dimension::_2D:
			drawable.draw(*this, state);
			break;
		case ikk::Draw::Dimension::_3D:
			drawable.draw(*this, state);
			break;
		case ikk::Draw::Dimension::_GUI:
			break;
		}
	}
}