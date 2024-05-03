#pragma once

#include <memory>

#include "InariKonKon/Graphics/PostFX/Effects/PostEffects.hpp"

namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;

	namespace priv
	{
		class PostFXManager;
	}

	class Scene
	{
	public:
		Scene(Application* const app = nullptr, const PostEffects effects = PostEffects::None) noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(Window& window) noexcept = 0;

		virtual void setPostFX(const PostEffects effects) noexcept final;
		//TODO:
		//Get...
	protected:
		Application* m_app;
	private:
		std::shared_ptr<priv::PostFXManager> m_postFXManager;

		friend class Window;
	};
}