#include "InariKonKon/Application/Application.hpp"

#include <print>

namespace ikk
{
	Application::Application(const char* const title, const glm::ivec2 size)
		try : m_window(title, size)
	{
	}
	catch (const std::exception& e)
	{
		std::print("Exception was thrown: {}", e.what());
		throw std::exception(e);
	}

	Window& Application::getWindow() noexcept
	{
		return this->m_window;
	}

	const Window& Application::getWindow() const noexcept
	{
		return this->m_window;
	}

	StateManager& Application::getStateManager() noexcept
	{
		return this->m_stateManager;
	}

	const StateManager& Application::getStateManager() const noexcept
	{
		return this->m_stateManager;
	}

	const bool Application::shouldClose() const noexcept
	{
		return this->m_window.shouldClose();
	}

	inline static bool NoStateWarnign = true;

	void Application::handleEvents() noexcept
	{
		this->m_stateManager.processChanges();
		this->m_window.handleEvents();
		if (this->m_stateManager.getActiveStates().size() == 0)
		{
			if (NoStateWarnign == true)
			{
				std::print("Application has no state!\n");
				NoStateWarnign = false;
			}
		}
		else
			NoStateWarnign = true;
	}

	void Application::update() noexcept
	{
		const Time dt = this->m_clock.restart();
		for (const auto& state : this->m_stateManager.getActiveStates())
			state->update(*this, dt);
	}

	void Application::render(const glm::vec4 clearColor) noexcept
	{
		for (const auto& state : this->m_stateManager.getActiveStates())
			state->draw(this->m_window);
		this->m_window.render(clearColor);

		if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
			while (this->m_clock.getElapsedTime().toDuration() < std::chrono::microseconds(1000000 / limit));
	}
}