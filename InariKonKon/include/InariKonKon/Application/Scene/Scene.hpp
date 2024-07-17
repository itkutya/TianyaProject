#pragma once

#include <cstdint>

//#include "InariKonKon/Graphics/PostFX/PostFX.hpp"
//#include "InariKonKon/Utility/Math/Vector2.hpp"

namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;
	class SceneManager;

	class Scene
	{
	public:
		typedef std::uint32_t SceneID;

		Scene(Application& app/*, const PostEffects effects = PostEffects::None*/) noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		//Handle incoming window events.
		virtual void handleEvents(const Event& event) noexcept = 0;
		//Update the game events.
		virtual void update(const Time& dt) noexcept = 0;
		//Update game events even if the scene is not active.
		virtual void softUpdate(const Time& dt) noexcept {};
		//Render scene to the window.
		virtual void render(const Window& window) const noexcept = 0;

		const SceneID& getID() const noexcept;

		//virtual void setPostFX(const PostEffects effects) noexcept final;
	protected:
		virtual const Application& getApplication() const noexcept final;
		virtual Application& getApplication() noexcept final;
	private:
		SceneID m_id;
		bool m_active = false;
		Application& m_app;
		//priv::PostFX m_postFX;

		friend class SceneManager;
		//[[nodiscard]] const priv::PostFX& getPostFXManager() const noexcept;
		//[[nodiscard]] priv::PostFX& getPostFXManager() noexcept;
		//void onResize(const vec2u newSize) noexcept;
	};
}