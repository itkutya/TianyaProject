#include "InariKonKon/Application/Scene/SceneManager.hpp"

#include <cassert>

#include "InariKonKon/Window/Event/Event.hpp"

namespace ikk
{
	void SceneManager::remove(const Scene& scene, const bool resetActiveScene) noexcept
	{
		this->m_removedScenes.emplace_back(scene.getID());

		if (resetActiveScene)
			this->resetActiveScene();
	}

	Scene& SceneManager::setActiveScene(Scene& scene) noexcept
	{
		if (this->m_activeScene != nullptr)
			this->m_activeScene->m_active = false;

		this->m_activeScene = &scene;
		this->m_activeScene->m_active = true;
		
		return *this->m_activeScene;
	}

	const Scene& SceneManager::getActiveScene() const noexcept
	{
		assert((this->m_activeScene != nullptr) && "There is no active scene!");
		return *this->m_activeScene;
	}

	Scene& SceneManager::getActiveScene() noexcept
	{
		assert((this->m_activeScene != nullptr) && "There is no active scene!");
		return *this->m_activeScene;
	}

	void SceneManager::resetActiveScene() noexcept
	{
		if (this->m_scenes.size() > 0)
			this->setActiveScene(*this->m_scenes.begin()->second.get());
	}

	void SceneManager::handleSceneChanges() noexcept
	{
		if (this->m_newScenes.size() > 0)
		{
			for (auto& scene : this->m_newScenes)
			{
				const auto id = scene->getID();
				auto inserted = this->m_scenes.try_emplace(id, std::move(scene));
				if (inserted.first->second->m_active)
					this->setActiveScene(*inserted.first->second.get());
			}
			this->m_newScenes.clear();
		}

		for (const auto& sceneID : this->m_removedScenes)
		{
			if (this->m_activeScene == this->m_scenes.at(sceneID).get())
				this->m_activeScene = nullptr;
			this->m_scenes.erase(sceneID);
		}
	}

	void SceneManager::dispatchEvent(const Event& event) noexcept
	{
		this->getActiveScene().handleEvents(event);
		//if (event.type == Event::Type::FrameBufferResized)
		//	this->getActiveScene().onResize({ event.size.width, event.size.height });
	}

	void SceneManager::update(const Time& dt) noexcept
	{
		this->getActiveScene().update(dt);

		for (const auto& scene : this->m_scenes)
			scene.second->softUpdate(dt);
	}

	void SceneManager::render(const Window& window) const noexcept
	{
		//this->getActiveScene().getPostFXManager().clear();
		//this->getActiveScene().getPostFXManager().activate();
		this->getActiveScene().render(window);
		//this->getActiveScene().getPostFXManager().display(window);
	}
}