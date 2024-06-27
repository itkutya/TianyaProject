#include "InariKonKon/Application/Application.hpp"

#include <thread>

namespace ikk
{
	Application::Application(const std::u8string_view title, const Window::Settings settings) noexcept : m_window(title.data(), settings)
	{
		this->m_clock.restart();
	}

	const bool Application::isOpen() noexcept
	{
		this->m_sceneManager.handleSceneChanges();
		return !this->m_window.shouldClose();
	}

	const Window& Application::getWindow() const noexcept
	{
		return this->m_window;
	}

	Window& Application::getWindow() noexcept
	{
		return this->m_window;
	}

	void Application::removeScene(const Scene& scene, const bool resetActiveScene) noexcept
	{
		this->m_sceneManager.remove(scene, resetActiveScene);
	}

	void Application::popLastScene(const bool resetActiveScene) noexcept
	{
		this->m_sceneManager.pop(resetActiveScene);
	}

	Scene& Application::setActiveScene(Scene& scene) noexcept
	{
		return this->m_sceneManager.setActiveScene(scene);
	}

	void Application::handleEvents() noexcept
	{
		this->m_window.handleEvents();
		std::queue<Event>& eventQueue = this->m_window.getEventQueue();
		for (; !eventQueue.empty(); eventQueue.pop())
			this->m_sceneManager.dispatchEvent(eventQueue.front());
	}

	void ikk::Application::update() noexcept
	{
		const Time& dt = this->m_clock.restart();
		this->m_sceneManager.update(dt);
	}

	void ikk::Application::render(const Color clearColor) const noexcept
	{
		this->m_window.clear(clearColor);
		this->m_sceneManager.render(this->m_window);
		this->m_window.render();
		this->halt();
	}

	void Application::halt() const noexcept
	{
		if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
		{
			const std::int64_t targetFPS = static_cast<std::int64_t>(1000000LL / limit);
			const std::int64_t sleepTime = targetFPS - this->m_clock.getElapsedTime().asMicroseconds();
			if (sleepTime > 0)
				std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
		}
	}
}