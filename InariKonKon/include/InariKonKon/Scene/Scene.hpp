#pragma once

namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;

	class Scene
	{
	public:
		Scene(Application* const app = nullptr) noexcept : m_app(app) {};

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(Window& window) noexcept = 0;
	protected:
		Application* m_app;
	};
}