#include "InariKonKon/Scene/Scene.hpp"

#include "InariKonKon/Application/Application.hpp"

ikk::Scene::Scene(Application& app, const PostEffects effects) noexcept
	: m_app(app), m_postFXManager(app.getWindow().getSize(), effects)
{
}

const ikk::Application& ikk::Scene::getApplication() const noexcept
{
	return this->m_app;
}

ikk::Application& ikk::Scene::getApplication() noexcept
{
	return this->m_app;
}

void ikk::Scene::setPostFX(const PostEffects effects) noexcept
{
	this->m_postFXManager.setEffects(effects);
}

const ikk::priv::PostFXManager& ikk::Scene::getPostFXManager() const noexcept
{
	return this->m_postFXManager;
}

ikk::priv::PostFXManager& ikk::Scene::getPostFXManager() noexcept
{
	return this->m_postFXManager;
}