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
		class SceneManager;
	}

	class Window final
	{
	public:
		struct Settings
		{
			VideoMode videomode;
			std::uint32_t fpslimit	= 60;
			bool vsync				= false;
			bool fullscreem			= false;
		};

		Window(const std::string& title, const Window::Settings settings);

		Window(const Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		[[nodiscard]] const bool shouldClose() const noexcept;
		void setActive(const bool active = true) const noexcept;

		void handleEvents() const noexcept;
		void clear(const Color clearColor) const noexcept;
		void render() const noexcept;

		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::string& getTitle() const noexcept;
		void setTitle(const std::string& title) noexcept;

		[[nodiscard]] const Vector2<std::uint32_t> getSize() const noexcept;
		void setSize(const Vector2<std::uint32_t> size) noexcept;
		
		template<Dimension T>
		void draw(const Drawable<T>& drawable, const RenderState& state = {}) const noexcept;
	private:
		std::uint32_t m_id;
		std::string m_title;
		GLFWwindow* m_window;
		Window::Settings m_settings;

		std::shared_ptr<priv::EventManager> m_eventManager;
		
		Scene* m_activeScene = nullptr;

		GLFWwindow* const create(const std::string& title, const VideoMode vm) const noexcept;
		void initWindowEvents() noexcept;

		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;

		void setDefaultFrameBufferActive() const noexcept;

		friend class Application;
		friend class priv::SceneManager;
	};

	template<Dimension T>
	inline void Window::draw(const Drawable<T>& drawable, const RenderState& state) const noexcept
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