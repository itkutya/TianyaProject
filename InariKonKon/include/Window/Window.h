#pragma once

#include <string>
#include <exception>

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"

struct GLFWwindow;
namespace ikk
{
	class Window final
	{
	public:
		Window(const char* const title, const glm::ivec2 size);

		Window(const Window&) noexcept = default;
		Window(Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		const bool shouldClose() const noexcept;

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const glm::vec4 clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;
	private:
		std::string m_title;
		GLFWwindow* m_window = nullptr;
	};
}