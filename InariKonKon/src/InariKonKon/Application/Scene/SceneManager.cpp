#include "InariKonKon/Application/Scene/SceneManager.hpp"

#include <cassert>

#include "InariKonKon/Window/Event/Event.hpp"

namespace ikk
{
	namespace priv
	{
		void SceneManager::remove(const Scene& scene, const bool resetActiveScene) noexcept
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

		void SceneManager::pop(const bool resetActiveScene) noexcept
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

		Scene& SceneManager::setActiveScene(Scene& scene) noexcept
		{
			this->m_activeScene = &scene;
			return *this->m_activeScene;
		}

		//TODO:
		//Impl...
		void SceneManager::handleSceneChanges() noexcept
		{
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

		void SceneManager::dispatchEvent(const Event& event) noexcept
		{
			this->getActiveScene().handleEvents(event);

			if (event.type == Event::Type::FrameBufferResized)
				this->getActiveScene().onResize({ event.size.width, event.size.height });
		}

		void SceneManager::update(const Time& dt) noexcept
		{
			this->getActiveScene().update(dt);
		}

		void SceneManager::render(const Window& window) const noexcept
		{
			//this->getActiveScene().getPostFXManager().clear();
			///this->getActiveScene().getPostFXManager().activate();
			this->getActiveScene().render(window);
			//this->getActiveScene().getPostFXManager().display(window);
		}

		void SceneManager::resetActiveScene() noexcept
		{
			if (this->m_scenes.size() > 0)
				this->setActiveScene(*this->m_scenes.back().get());
		}
	}
}