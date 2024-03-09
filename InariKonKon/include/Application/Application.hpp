#pragma once

#include <utility>

#include "Window/Window.h"

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

		template <class Self>
		auto& getWindow(this Self&& self) noexcept;

		const bool shouldClose() const noexcept;

		void handleEvents() noexcept;
		void update() noexcept;
		void render(const glm::vec4 clearColor = { 0.f, 0.f, 0.f, 1.f }) noexcept;
	private:
		Window m_window;
	};

	template<class Self>
	inline auto& Application::getWindow(this Self&& self) noexcept
	{
		return std::forward<Self>(self).m_window;
	}
}