#include "InariKonKon/SceneManager/SceneManager.hpp"

ikk::Scene* const ikk::priv::SceneManager::emplace(std::unique_ptr<ikk::Scene>&& scene, const bool setItAsActiveScene) noexcept
{
	Scene* const newScene = this->m_scenes.emplace_back(std::move(scene)).get();
	if (setItAsActiveScene)
		this->m_activeScene = newScene;
	return newScene;
}

void ikk::priv::SceneManager::remove(const ikk::Scene* scene, const bool resetActiveScene) noexcept
{
	if (scene != nullptr)
	{
		if (this->m_activeScene == scene)
			this->m_activeScene = nullptr;

		this->m_scenes.erase(std::remove_if(this->m_scenes.begin(), this->m_scenes.end(), [&scene](const std::unique_ptr<ikk::Scene>& s)
			{
				return s.get() == scene;
			}), this->m_scenes.end());

		if (resetActiveScene && this->m_scenes.size() > 0)
			this->m_activeScene = this->m_scenes.back().get();
	}
}

void ikk::priv::SceneManager::pop(const bool resetActiveScene) noexcept
{
	if (this->m_scenes.size() > 0)
	{
		if (this->m_activeScene == this->m_scenes.back().get())
		{
			this->m_activeScene = nullptr;
			if (this->m_scenes.size() > 1 && resetActiveScene)
				this->m_activeScene = (this->m_scenes.end() - 2)->get();
		}
		this->m_scenes.pop_back();
	}
}

ikk::Scene* const ikk::priv::SceneManager::setActiveScene(ikk::Scene* scene) noexcept
{
	this->m_activeScene = scene;
	return this->m_activeScene;
}

const ikk::Scene* const ikk::priv::SceneManager::getActiveScene() const noexcept
{
	return this->m_activeScene;
}

ikk::Scene* const ikk::priv::SceneManager::getActiveScene() noexcept
{
	return this->m_activeScene;
}