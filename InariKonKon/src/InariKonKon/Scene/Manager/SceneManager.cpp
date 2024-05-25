#include "InariKonKon/Scene/Manager/SceneManager.hpp"

#include <cassert>

#include "InariKonKon/Application/Application.hpp"
#include "InariKonKon/Window/Window.hpp"

void ikk::priv::SceneManager::remove(const ikk::Scene& scene, const bool resetActiveScene) noexcept
{
	if (this->m_activeScene == &scene)
		this->m_activeScene = nullptr;

	this->m_scenes.erase(std::remove_if(this->m_scenes.begin(), this->m_scenes.end(), [&scene](const std::shared_ptr<ikk::Scene>& s)
		{
			return s.get() == &scene;
		}), this->m_scenes.end());

	if (resetActiveScene)
		this->resetActiveScene();
}

void ikk::priv::SceneManager::pop(const bool resetActiveScene) noexcept
{
	if (this->m_scenes.size() > 0)
	{
		if (this->m_activeScene == this->m_scenes.back().get())
			this->m_activeScene = nullptr;
		this->m_scenes.pop_back();
	}

	if (resetActiveScene)
		this->resetActiveScene();
}

ikk::Scene& ikk::priv::SceneManager::setActiveScene(ikk::Scene& scene) noexcept
{
	this->m_activeScene = &scene;
	return *this->m_activeScene;
}

const ikk::Scene& ikk::priv::SceneManager::getActiveScene() const noexcept
{
	assert(this->m_activeScene != nullptr && "There is no active scene!");
	return *this->m_activeScene;
}

ikk::Scene& ikk::priv::SceneManager::getActiveScene() noexcept
{
	assert(this->m_activeScene != nullptr && "There is no active scene!");
	return *this->m_activeScene;
}

void ikk::priv::SceneManager::resetActiveScene() noexcept
{
	if (this->m_scenes.size() > 0)
		this->setActiveScene(*this->m_scenes.back().get());
}