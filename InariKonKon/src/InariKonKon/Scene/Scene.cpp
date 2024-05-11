#include "InariKonKon/Scene/Scene.hpp"

#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"
#include "InariKonKon/Application/Application.hpp"

ikk::Scene::Scene(Application& app, const PostEffects effects) noexcept
	: m_app(app), m_postFXManager(std::make_shared<priv::PostFXManager>(app.getWindow().getSize(), effects))
{
}

void ikk::Scene::setPostFX(const PostEffects effects) noexcept
{
	this->m_postFXManager->setEffects(effects);
}

const ikk::Application& ikk::Scene::getApplication() const noexcept
{
	return this->m_app;
}

ikk::Application& ikk::Scene::getApplication() noexcept
{
	return this->m_app;
}

void ikk::Scene::applyPostFX() const noexcept
{
	this->m_postFXManager->getFrameBuffer().bind();
}