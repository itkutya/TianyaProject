#pragma once

#include <utility>

#include "Window/Window.h"

class Application final
{
public:
	Application(const char* const title);

	Application(const Application&) noexcept = default;
	Application(Application&) noexcept = default;
	Application(Application&&) noexcept = default;
	
	Application& operator=(const Application&) noexcept = default;
	Application& operator=(Application&) noexcept = default;
	Application& operator=(Application&&) noexcept = default;

	~Application() noexcept = default;

	template <class Self>
	auto& getWindow(this Self&& self) noexcept;
private:
	Window m_window;
};

template<class Self>
inline auto& Application::getWindow(this Self&& self) noexcept
{
	return std::forward<Self>(self).m_window;
}