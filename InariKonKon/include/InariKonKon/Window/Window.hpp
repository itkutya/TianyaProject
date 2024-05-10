#pragma once

#include <exception>
#include <print>
#include <string>
#include <queue>
#include <memory>

#include "InariKonKon/Utility/Math/Vector2.hpp"
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

		[[nodiscard]] const std::uint32_t& getID() const noexcept;
		[[nodiscard]] const bool shouldClose() const noexcept;

		void handleEvents() noexcept;
		void clear(const Color clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;
		void render() noexcept;

		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::string& getTitle() const noexcept;
		void setTitle(const std::string& title) noexcept;

		[[nodiscard]] const Vector2<std::uint32_t> getSize() const noexcept;
		void setSize(const Vector2<std::uint32_t> size) noexcept;

		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;

		void setActive(const bool active = true) const noexcept;
		void setDefaultFrameBufferActive() noexcept;
		
		template<Dimension T>
		void draw(Drawable<T>& drawable, const RenderState& state = {}) noexcept;
	private:
		std::uint32_t m_id;
		GLFWwindow* m_window;
		std::string m_title;
		Window::Settings m_settings;
		VideoMode m_videmode;

		std::shared_ptr<priv::EventManager> m_events;
		
		Scene* m_activeScene = nullptr;

		GLFWwindow* const create(const std::string& title, const VideoMode vm) const noexcept;
		void initWindowEvents() noexcept;

		friend class Application;
	};

	template<Dimension T>
	inline void Window::draw(Drawable<T>& drawable, const RenderState& state) noexcept
	{
		if (this->m_activeScene)
		{
			switch (T)
			{
			case ikk::Dimension::_2D: [[fallthrough]];
			case ikk::Dimension::_3D:
				if (state.applyPostFX)
					this->m_activeScene->applyPostFX();
				else
					this->setDefaultFrameBufferActive();
				drawable.draw(*this, state);
				break;
			case ikk::Dimension::_GUI:
				break;
			}
		}
	}
}