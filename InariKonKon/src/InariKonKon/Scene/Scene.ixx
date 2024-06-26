export module Scene;

export import Vector2;

import PostFX;

namespace ikk
{
	namespace priv
	{
		class SceneManager;
	}
}

export namespace ikk
{
	struct Event;
	class Time;
	class Window;
	class Application;

	class Scene
	{
	public:
		Scene(Application& app, const vec2u screenSize, const PostEffects effects = PostEffects::None) noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(const Window& window) const noexcept = 0;

		virtual void setPostFX(const PostEffects effects) noexcept final;
	protected:
		virtual const Application& getApplication() const noexcept final;
		virtual Application& getApplication() noexcept final;
	private:
		Application& m_app;
		PostFX m_postFX;

		friend class priv::SceneManager;
		[[nodiscard]] const PostFX& getPostFXManager() const noexcept;
		[[nodiscard]] PostFX& getPostFXManager() noexcept;
		void onResize(const vec2u newSize) noexcept;
	};
	//TODO:
	//FIX ME...
	Scene::Scene(Application& app, const vec2u screenSize, const PostEffects effects) noexcept : m_app(app), m_postFX(screenSize, effects)
	{
	}

	void Scene::setPostFX(const PostEffects effects) noexcept
	{
		this->m_postFX.setEffects(effects);
	}

	const Application& Scene::getApplication() const noexcept
	{
		return this->m_app;
	}

	Application& Scene::getApplication() noexcept
	{
		return this->m_app;
	}

	const PostFX& Scene::getPostFXManager() const noexcept
	{
		return this->m_postFX;
	}

	PostFX& Scene::getPostFXManager() noexcept
	{
		return this->m_postFX;
	}

	void Scene::onResize(const vec2u newSize) noexcept
	{
		this->getPostFXManager().getFrameBuffer().resize(newSize);
	}
}