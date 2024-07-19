#include "InariKonKon/Application/Application.hpp"

#include <thread>
#include <exception>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace ikk
{
	namespace priv
	{
		struct Libraries
		{
			static const Libraries* const init()
			{
				if (!glfwInit())
					throw std::exception("Cannot initialize glfw.");;
				return nullptr;
			}
		};
		inline static const Libraries* const lib = Libraries::init();
	}

	Application::Application(const std::u8string_view title, const Window::Settings settings) noexcept : m_window(title.data(), settings)
	{
		this->m_clock.restart();
	}

	const Window& Application::getWindow() const noexcept
	{
		return this->m_window;
	}

	Window& Application::getWindow() noexcept
	{
		return this->m_window;
	}

	const SceneManager& Application::getSceneManager() const noexcept
	{
		return this->m_sceneManager;
	}

	SceneManager& Application::getSceneManager() noexcept
	{
		return this->m_sceneManager;
	}

	void Application::run(const Color clearColor) noexcept
	{
		while (this->isOpen())
		{
			const Time& dt = this->m_clock.restart();

			this->m_sceneManager.handleSceneChanges();

			this->handleEvents();
			this->update(dt);
			this->render(clearColor);
		}
	}

	const bool Application::isOpen() noexcept
	{
		this->m_sceneManager.handleSceneChanges();
		return !this->m_window.shouldClose();
	}

	void Application::handleEvents() noexcept
	{
		this->m_window.handleEvents();
		std::queue<Event>& eventQueue = this->m_window.getEventQueue();
		for (; !eventQueue.empty(); eventQueue.pop())
			this->m_sceneManager.dispatchEvent(eventQueue.front());
	}

	void ikk::Application::update(const Time& dt) noexcept
	{
		this->m_sceneManager.update(dt);
	}

	void ikk::Application::render(const Color clearColor) const noexcept
	{
		this->m_window.clear(clearColor);
		this->m_sceneManager.render(this->m_window);
		this->m_window.render();

		if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
			this->sleep(limit);
	}

	void Application::sleep(const std::uint32_t amountSeconds) const noexcept
	{
		const std::int64_t targetFPS = static_cast<std::int64_t>(1000000LL / amountSeconds);
		const std::int64_t sleepTime = targetFPS - this->m_clock.getElapsedTime().asMicroseconds();
		if (sleepTime > 0)
			std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	}
}