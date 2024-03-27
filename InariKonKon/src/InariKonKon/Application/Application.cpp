#include "InariKonKon/Application/Application.hpp"

#include <print>
#include <exception>

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

	SceneManager& Application::getSceneManager() noexcept
	{
		return this->m_sceneManager;
	}

	const SceneManager& Application::getSceneManager() const noexcept
	{
		return this->m_sceneManager;
	}

	const bool Application::isOpen() const noexcept
	{
		return !this->m_window.shouldClose();
	}

	void Application::handleEvents() noexcept
	{
		this->m_sceneManager.processChanges();

		this->m_window.handleEvents();
		for (; !this->m_window.getEventQueue().empty(); this->m_window.getEventQueue().pop())
			this->m_sceneManager.getActiveScene()->processEvent(this->m_window.getEventQueue().front());
	}

	void Application::update() noexcept
	{
		const Time dt = this->m_clock.restart();
		this->m_sceneManager.getActiveScene()->update(dt);
	}

	void Application::render(const glm::vec4 clearColor) noexcept
	{
		this->m_window.clear(clearColor);
		this->m_sceneManager.getActiveScene()->draw(this->m_window);
		this->m_window.render();

		if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
			while (this->m_clock.getElapsedTime().toDuration() < std::chrono::microseconds(1000000 / limit));
	}
}