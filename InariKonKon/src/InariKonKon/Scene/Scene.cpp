#include "InariKonKon/Scene/Scene.hpp"

ikk::Scene::Scene(Application* const app, const PostEffect effects) noexcept : m_app(app), m_postprocesser(effects)
{
}

void ikk::Scene::setPostFX(const PostEffect effects) noexcept
{
	this->m_postprocesser.setEffects(effects);
}

const ikk::priv::Postprocesser& ikk::Scene::getPostprocesser() const noexcept
{
	return this->m_postprocesser;
}

ikk::priv::Postprocesser& ikk::Scene::getPostprocesser() noexcept
{
	return this->m_postprocesser;
}