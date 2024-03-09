#include "Application/Application.hpp"

#include <print>

Application::Application(const char* const title, const glm::ivec2 size) try : m_window(title, size)
{
}
catch (const std::exception& e)
{
	std::print("Exception was thrown: {}", e.what());
	throw std::exception(e);
}

const bool Application::shouldClose() const noexcept
{
	return this->m_window.shouldClose();
}

void Application::handleEvents() noexcept
{
	this->m_window.handleEvents();
}

void Application::update() noexcept
{
	this->m_window.update();
}

void Application::render(const glm::vec4 clearColor) noexcept
{
	this->m_window.render(clearColor);
}