#pragma once

#include <string>
#include <queue>

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

#include "InariKonKon/Event/Event.hpp"

struct GLFWwindow;

namespace ikk
{
	struct WindowSettigns
	{
		bool vsync = true;
		std::uint32_t fpslimit = 0;
		bool fullscreem = false;
	};

	class Window final
	{
	public:
		Window(const char* const title, const glm::ivec2 size, const WindowSettigns settings = WindowSettigns());

		Window(const Window&) noexcept = default;
		Window(Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		const std::queue<Event>& getEventQueue() const noexcept;
		std::queue<Event>& getEventQueue() noexcept;

		[[nodiscard]] const bool shouldClose() const noexcept;

		void setFPSLimit(const std::uint32_t limit) noexcept;
		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;

		void setVSync(const bool vsync) noexcept;
		[[nodiscard]] const bool isVSyncEnabled() const noexcept;

		void handleEvents() noexcept;
		void clear(const glm::vec4 clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;
		void render() noexcept;
	private:
		GLFWwindow* m_window = nullptr;
		std::string m_title;
		WindowSettigns m_settings;
	};
}