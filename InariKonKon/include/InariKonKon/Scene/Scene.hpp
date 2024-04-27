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
		Scene(Application* const app = nullptr, const PostEffect effects = PostEffect::None) noexcept;

		Scene(const Scene&) noexcept = default;
		Scene(Scene&&) noexcept = default;

		virtual Scene& operator=(const Scene&) noexcept = default;
		virtual Scene& operator=(Scene&&) noexcept = default;

		virtual ~Scene() noexcept = default;

		virtual void handleEvents(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void render(Window& window) noexcept = 0;

		virtual void setPostFX(const PostEffect effects) noexcept final;
	protected:
		Application* m_app;
	private:
		priv::Postprocesser m_postprocesser;

		virtual const	priv::Postprocesser& getPostprocesser() const	noexcept final;
		virtual			priv::Postprocesser& getPostprocesser()			noexcept final;

		friend class Application;
	};
}