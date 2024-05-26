#pragma once

#include <memory>

//#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

//#include "InariKonKon/Graphics/PostFX/PostEffects.hpp"

namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;

	namespace priv
	{
		class SceneManager;
	}

	class Scene
	{
	public:
		Scene(Application& app/*, const PostEffects effects = PostEffects::None*/) noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(const Window& window) const noexcept = 0;

		//virtual void setPostFX(const PostEffects effects) noexcept final;
	protected:
		virtual const Application& getApplication() const noexcept final;
		virtual Application& getApplication() noexcept final;
	private:
		Application& m_app;
		//priv::PostFXManager m_postFXManager;

		friend class Application;
		//[[nodiscard]] const priv::PostFXManager& getPostFXManager() const noexcept;
		//[[nodiscard]] priv::PostFXManager& getPostFXManager() noexcept;
	};
}