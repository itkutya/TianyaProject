#include "Application.hpp"

Application::Application(const char* const title) noexcept : m_title(title)
{
}

const bool Application::shouldClose() const noexcept
{
	return false;
}

void Application::handleEvents() noexcept
{
}

void Application::update() noexcept
{
}

void Application::draw() noexcept
{
}