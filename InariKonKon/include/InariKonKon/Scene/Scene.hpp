#pragma once

#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;

	class Scene
	{
	public:
		inline Scene(Application* const app = nullptr, const PostEffects effects = PostEffects::None) noexcept : m_app(app), m_postFXManager(effects) {};

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(Window& window) noexcept = 0;

		inline virtual void setPostFX(const PostEffects effects) noexcept final { this->m_postFXManager.setEffects(effects); };
		//TODO:
		//Get...
	protected:
		Application* m_app;
	private:
		priv::PostFXManager m_postFXManager;
	};
}