#pragma once

#include <string_view>

#include "InariKonKon/Application/Scene/SceneManager.hpp"
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

		[[nodiscard]] const Window& getWindow() const noexcept;
		[[nodiscard]] Window& getWindow() noexcept;

		[[nodiscard]] const SceneManager& getSceneManager() const noexcept;
		[[nodiscard]] SceneManager& getSceneManager() noexcept;

		void run(const Color clearColor = Color::Black) noexcept;
	private:
		Window m_window;
		Clock m_clock{};
		SceneManager m_sceneManager{};

		[[nodiscard]] const bool isOpen() noexcept;

		void handleEvents() noexcept;
		void update(const Time& dt) noexcept;
		void render(const Color clearColor) const noexcept;
		void sleep(const std::uint32_t amountSeconds) const noexcept;
	};
}