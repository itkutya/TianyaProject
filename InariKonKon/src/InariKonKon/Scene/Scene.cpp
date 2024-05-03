#include "InariKonKon/Scene/Scene.hpp"

#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

ikk::Scene::Scene(Application* const app, const PostEffects effects) noexcept : m_app(app), m_postFXManager(std::make_shared<priv::PostFXManager>(effects))
{
}

void ikk::Scene::setPostFX(const PostEffects effects) noexcept
{
	this->m_postFXManager->setEffects(effects);
}