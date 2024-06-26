#pragma once

#include <string_view>

#include "InariKonKon/Scene/SceneManager.hpp"
#include "InariKonKon/Utility/Clock.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
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
}