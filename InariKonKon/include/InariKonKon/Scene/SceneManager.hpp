#pragma once

#include <vector>
#include <memory>

#include "InariKonKon/Utility/TypeDefs.hpp"
#include "InariKonKon/Scene/Scene.hpp"

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
	}
}