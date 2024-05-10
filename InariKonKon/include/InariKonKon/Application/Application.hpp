#pragma once

#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Clock.hpp"

namespace ikk
{
	namespace priv
	{
		class SceneManager;
	}

	class Application final
	{
	public:
		Application(const std::string& title, const VideoMode vm);

		Application(const Application&) noexcept = default;
		Application(Application&&) noexcept = default;

		Application& operator=(const Application&) noexcept = default;
		Application& operator=(Application&&) noexcept = default;

		~Application() noexcept = default;

		[[nodiscard]] const bool isOpen() const noexcept;

		[[nodiscard]] const Window& getWindow() const noexcept;
		[[nodiscard]] Window& getWindow() noexcept;

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;

		Scene* const addScene(std::unique_ptr<Scene>&& scene, const bool setItAsActiveScene = true) noexcept;
		void removeScene(const Scene* scene, const bool resetActiveScene = false) noexcept;
		void popLastScene(const bool resetActiveScene = false) noexcept;

		Scene* const setActiveScene(Scene* scene) noexcept;
		[[nodiscard]] const Scene* const getActiveScene() const noexcept;
		[[nodiscard]] Scene* const getActiveScene() noexcept;
	private:
		Window m_window;
		Clock m_clock;
		std::shared_ptr<priv::SceneManager> m_sceneManager;
	};
}