module;

#include <cassert>

export module SceneManager;

import <vector>;
import <memory>;

export import Window;
export import Color;
export import Event;
export import Time;

import Typedefs;
import Scene;

export namespace ikk
{
	export namespace priv
	{
		class SceneManager final
		{
		public:
			SceneManager() noexcept = default;

			SceneManager(const SceneManager&) noexcept = default;
			SceneManager(SceneManager&&) noexcept = default;

			SceneManager& operator=(const SceneManager&) noexcept = default;
			SceneManager& operator=(SceneManager&&) noexcept = default;

			~SceneManager() noexcept = default;

			template<SceneType T>
			Scene& add(const T&& scene, const bool setItAsActiveScene);
			void remove(const Scene& scene, const bool resetActiveScene) noexcept;
			void pop(const bool resetActiveScene) noexcept;

			Scene& setActiveScene(Scene& scene) noexcept;

			void dispatchEvent(const Event& event) noexcept;
			void update(const Time& dt) noexcept;
			void render(const Window& window) const noexcept;
		private:
			std::vector<std::shared_ptr<Scene>> m_scenes;
			Scene* m_activeScene = nullptr;

			void resetActiveScene() noexcept;

			[[nodiscard]] const Scene& getActiveScene() const noexcept;
			[[nodiscard]] Scene& getActiveScene() noexcept;
		};

		template<SceneType T>
		Scene& SceneManager::add(const T&& scene, const bool setItAsActiveScene)
		{
			Scene& newScene = *this->m_scenes.emplace_back(std::make_shared<T>(std::move(scene))).get();
			if (setItAsActiveScene)
				this->setActiveScene(newScene);
			return newScene;
		}

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
			this->getActiveScene().getPostFXManager().clear();
			this->getActiveScene().getPostFXManager().activate();
			this->getActiveScene().render(window);
			this->getActiveScene().getPostFXManager().display(window);
		}

		void SceneManager::resetActiveScene() noexcept
		{
			if (this->m_scenes.size() > 0)
				this->setActiveScene(*this->m_scenes.back().get());
		}
	}
}