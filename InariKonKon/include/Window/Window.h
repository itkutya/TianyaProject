#pragma once

#include <string>

struct GLFWwindow;

class Window final
{
public:
	Window(const char* const title);

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
	void render() noexcept;
private:
	std::string m_title;
	GLFWwindow* m_window = nullptr;
};