#pragma once

#include <exception>
#include <print>
#include <string>
#include <queue>
#include <memory>

#include "InariKonKon/Window/Event/Event.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"
#include "InariKonKon/Window/VideoMode.hpp"
#include "InariKonKon/Utility/Color.hpp"
#include "InariKonKon/Scene/Scene.hpp"

struct GLFWwindow;

namespace ikk
{
	namespace priv
	{
		class EventManager;
	}

	class Window final
	{
	public:
		struct Settings
		{
			std::uint32_t fpslimit	= 60;
			bool vsync				= false;
			bool fullscreem			= false;
		};

		Window(const std::string& title, const VideoMode vm, const Window::Settings settings = {});

		Window(const Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		[[nodiscard]] const bool shouldClose() const noexcept;

		void handleEvents() noexcept;
		void clear(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) const noexcept;
		void render() noexcept;

		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::string& getTitle() const noexcept;
		void getTitle(const std::string& title) noexcept;

		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;

		void setActive(const bool active = true) const noexcept;
		
		void draw(Drawable& drawable, const RenderState& state = {}) const noexcept;
		//Draw primitives, like with arrays & stuff...
		//void draw() const noexcept;
	private:
		GLFWwindow* m_window;
		std::string m_title;
		Window::Settings m_settings;

		std::shared_ptr<priv::EventManager> m_events;
		
		Scene* m_activeScene = nullptr;

		GLFWwindow* const create(const std::string& title, const VideoMode vm) const noexcept;
		void initWindowEvents() noexcept;

		friend class Application;
	};
}