#pragma once

#include "InariKonKon/Window/Window.hpp"
#include "InariKonKon/Utility/Clock.hpp"
#include "InariKonKon/Scene/SceneManager.hpp"

namespace ikk
{
	class Application final
	{
	public:
		Application(const char* const title, const glm::ivec2 size);

		Application(const Application&) noexcept = default;
		Application(Application&) noexcept = default;
		Application(Application&&) noexcept = default;

		Application& operator=(const Application&) noexcept = default;
		Application& operator=(Application&) noexcept = default;
		Application& operator=(Application&&) noexcept = default;

		~Application() noexcept = default;

		[[nodiscard]] Window& getWindow() noexcept;
		[[nodiscard]] const Window& getWindow() const noexcept;
		[[nodiscard]] SceneManager& getSceneManager() noexcept;
		[[nodiscard]] const SceneManager& getSceneManager() const noexcept;

		[[nodiscard]] const bool isOpen() const noexcept;

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const glm::vec4 clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;
	private:
		Window m_window;
		Clock m_clock;
		SceneManager m_sceneManager;
	};
}