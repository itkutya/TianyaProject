#pragma once

#include <exception>
#include <print>
#include <string_view>

#include "InariKonKon/Window/VideoMode.hpp"
#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Window/Event/EventManager.hpp"

#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

struct GLFWwindow;

namespace ikk
{
	class Window final
	{
	public:
		struct Settings
		{
			std::uint32_t fpslimit	= 60;
			bool vsync				= false;
			bool fullscreem			= false;
		};

		Window(const std::string_view title, const VideoMode vm, const Window::Settings settings = {});

		Window(const Window&) noexcept = default;
		Window(Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		[[nodiscard]] const bool shouldClose() const noexcept;

		void handleEvents() noexcept;
		void clear(const Color clearColor) const noexcept;
		void render() noexcept;

		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::string_view getTitle() const noexcept;
		void getTitle(const std::string_view title) noexcept;

		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;

		void setActive(const bool active = true) const noexcept;
	private:
		GLFWwindow* m_window;
		std::string_view m_title;
		Window::Settings m_settings;

		priv::EventManager m_events;

		GLFWwindow* const create(const std::string_view title, const VideoMode vm) const noexcept;
		void initWindowEvents() noexcept;

		Triangle* triangle;
	};
}