module;
//Some cpp libs are still messed up...
#include <thread>

export module InariKonKon:Application;

import <string_view>;

export import :Window;
export import :Clock;

//#include "InariKonKon/Scene/Manager/SceneManager.hpp"

export namespace ikk
{
	class Application final
	{
	public:
		Application(const std::string_view title, const Window::Settings settings) noexcept;

		Application(const Application&) noexcept = default;
		Application(Application&&) noexcept = default;

		Application& operator=(const Application&) noexcept = default;
		Application& operator=(Application&&) noexcept = default;

		~Application() noexcept = default;

		[[nodiscard]] const bool isOpen() const noexcept;

		[[nodiscard]] const Window& getWindow() const noexcept;
		[[nodiscard]] Window& getWindow() noexcept;

		//[[nodiscard]] const SceneManager& getSceneManager() const noexcept;
		//[[nodiscard]] SceneManager& getSceneManager() noexcept;

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) const noexcept;
	private:
		Window m_window;
		Clock m_clock{};
		//SceneManager m_sceneManager{};
	};

	Application::Application(const std::string_view title, const Window::Settings settings) noexcept : m_window(title.data(), settings)
	{
		this->m_clock.restart();
	}

	const bool Application::isOpen() const noexcept
	{
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

	void Application::handleEvents() noexcept
	{
		this->m_window.handleEvents();
		//std::queue<Event>& eventQueue = this->m_window.getEventManager().getEventQueue();
		//for (; !eventQueue.empty(); eventQueue.pop())
		//	this->m_sceneManager.getActiveScene().handleEvents(eventQueue.front());
	}

	void ikk::Application::update() noexcept
	{
		const Time& dt = this->m_clock.restart();
		//this->m_sceneManager.getActiveScene().update(dt);
	}

	void ikk::Application::render(const Color clearColor) const noexcept
	{
		this->m_window.clear(clearColor);
		/*
		if (this->m_sceneManager.getActiveScene().getPostFXManager().getActiveEffetcts() != PostEffects::None)
		{
			this->m_sceneManager.getActiveScene().getPostFXManager().clear();
			this->m_sceneManager.getActiveScene().getPostFXManager().getFrameBuffer().bind();
		}
		else
			this->m_sceneManager.getActiveScene().getPostFXManager().setDefaultFrameBuffer();
		*/
		//this->m_sceneManager.getActiveScene().render(this->m_window);
		//this->m_sceneManager.getActiveScene().getPostFXManager().render(this->m_window);
		this->m_window.render();

		if (const std::uint32_t limit = 60; limit > 0)
		{
			const std::int64_t targetFPS = static_cast<std::int64_t>(1000000LL / limit);
			const std::int64_t sleepTime = targetFPS - this->m_clock.getElapsedTime().asMicroseconds();
			if (sleepTime > 0)
				std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
		}
	}
}