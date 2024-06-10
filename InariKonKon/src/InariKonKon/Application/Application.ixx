export module Application;

import <string_view>;

//#include "InariKonKon/Scene/Manager/SceneManager.hpp"

//#include "InariKonKon/Window/Window.hpp"
//#include "InariKonKon/Utility/Clock.hpp"

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

		[[nodiscard]] const SceneManager& getSceneManager() const noexcept;
		[[nodiscard]] SceneManager& getSceneManager() noexcept;

		void handleEvents() noexcept;
		void updateVectors() noexcept;
		void render(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) const noexcept;
	private:
		Window m_window;
		Clock m_clock{};
		SceneManager m_sceneManager{};
	};
}