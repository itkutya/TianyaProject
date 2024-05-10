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
		Scene(Application& app, const PostEffects effects = PostEffects::None) noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(Window& window) noexcept = 0;

		virtual void setPostFX(const PostEffects effects) noexcept final;
	protected:
		Application& m_app;
	private:
		std::shared_ptr<priv::PostFXManager> m_postFXManager;

		void applyPostFX() const noexcept;
		
		friend class Window;
	};
}