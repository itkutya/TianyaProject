#pragma once

#include "InariKonKon/Graphics/Postprocessing/Postprocesser.hpp"

namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;

	class Scene
	{
	public:
		Scene(Application* const app = nullptr, const PostEffect effects = PostEffect::None) noexcept : m_app(app), m_postprocesser(effects) {};

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(Window& window) noexcept = 0;

		virtual const	Postprocesser& getPostprocesser() const	noexcept final { return this->m_postprocesser; };
		virtual			Postprocesser& getPostprocesser()		noexcept final { return this->m_postprocesser; };
	protected:
		Application* m_app;
	private:
		Postprocesser m_postprocesser;
	};
}