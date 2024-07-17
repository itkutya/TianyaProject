#include "InariKonKon/Application/Scene/Scene.hpp"

#include "InariKonKon/Application/Application.hpp"

namespace ikk
{
	Scene::Scene(Application& app/*, const PostEffects effects*/) noexcept : m_app(app)//, m_postFX(app.getWindow().getSize(), effects)
	{
	}

	/*
	void Scene::setPostFX(const PostEffects effects) noexcept
	{
		this->m_postFX.setEffects(effects);
	}
	*/

	const Application& Scene::getApplication() const noexcept
	{
		return this->m_app;
	}

	Application& Scene::getApplication() noexcept
	{
		return this->m_app;
	}

	/*
	const priv::PostFX& Scene::getPostFXManager() const noexcept
	{
		return this->m_postFX;
	}

	priv::PostFX& Scene::getPostFXManager() noexcept
	{
		return this->m_postFX;
	}

	void Scene::onResize(const vec2u newSize) noexcept
	{
		this->getPostFXManager().getFrameBuffer().resize(newSize);
	}
	*/
}