export module Application;

import <string_view>;
import <thread>;

export import Clock;

import SceneManager;

export namespace ikk
{
	class Application final
	{
	public:
		Application(const std::u8string_view title, const Window::Settings settings) noexcept;

		Application(const Application&) noexcept = default;
		Application(Application&&) noexcept = default;

		Application& operator=(const Application&) noexcept = default;
		Application& operator=(Application&&) noexcept = default;

		~Application() noexcept = default;

		[[nodiscard]] const bool isOpen() const noexcept;

		[[nodiscard]] const Window& getWindow() const noexcept;
		[[nodiscard]] Window& getWindow() noexcept;

		template<SceneType T>
		Scene& addScene(const T&& scene, const bool setItAsActiveScene = true);
		void removeScene(const Scene& scene, const bool resetActiveScene = true) noexcept;
		void popLastScene(const bool resetActiveScene = true) noexcept;

		Scene& setActiveScene(Scene& scene) noexcept;

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) const noexcept;
	private:
		Window m_window;
		Clock m_clock{};
		priv::SceneManager m_sceneManager{};
	};

	Application::Application(const std::u8string_view title, const Window::Settings settings) noexcept : m_window(title.data(), settings)
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

	template<SceneType T>
	Scene& Application::addScene(const T&& scene, const bool setItAsActiveScene)
	{
		return this->m_sceneManager.add<T>(std::move(scene), setItAsActiveScene);
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

		if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
		{
			const std::int64_t targetFPS = static_cast<std::int64_t>(1000000LL / limit);
			const std::int64_t sleepTime = targetFPS - this->m_clock.getElapsedTime().asMicroseconds();
			if (sleepTime > 0)
				std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
		}
	}
}