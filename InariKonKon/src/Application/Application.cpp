#include "Application/Application.hpp"

#include <print>
#include <exception>

Application::Application(const char* const title) try : m_window(title)
{
}
catch (const std::exception& e)
{
	std::print("Exception was thrown: {}", e.what());
	throw std::exception(e);
}