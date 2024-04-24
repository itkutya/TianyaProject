#pragma once

#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Clock.hpp"
#include "InariKonKon/Scene/SceneManager.hpp"

namespace ikk
{
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

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;

		template<priv::SceneType T>
		Scene* const addScene(T&& scene, const bool setItAsActiveScene = true) noexcept;
		void removeScene(const Scene* scene, const bool resetActiveScene = false) noexcept;
		void popLastScene(const bool resetActiveScene = false) noexcept;

		Scene* const setActiveScene(Scene* scene) noexcept;
		[[nodiscard]] const Scene* const getActiveScene() const noexcept;
		[[nodiscard]] Scene* const getActiveScene() noexcept;
	private:
		Window m_window;
		Clock m_clock;
		priv::SceneManager m_sceneManager;
	};
	
	template<priv::SceneType T>
	inline Scene* const Application::addScene(T&& scene, const bool setItAsActiveScene) noexcept
	{
		return this->m_sceneManager.emplace<T>(std::move(scene), setItAsActiveScene);
	}
}