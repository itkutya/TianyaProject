#pragma once

#include <vector>
#include <memory>

#include "InariKonKon/Utility/TypeDefs.hpp"
#include "InariKonKon/Scene/Scene.hpp"

namespace ikk
{
	namespace priv
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

			template<SceneType T, class... Args>
			Scene& add(const bool setItAsActiveScene = true, Args&&... args);
			void remove(const Scene& scene, const bool resetActiveScene) noexcept;
			void pop(const bool resetActiveScene) noexcept;

			Scene& setActiveScene(Scene& scene) noexcept;
			[[nodiscard]] const Scene& getActiveScene() const noexcept;
			[[nodiscard]] Scene& getActiveScene() noexcept;
		private:
			std::vector<std::shared_ptr<Scene>> m_scenes;
			Scene* m_activeScene = nullptr;

			void resetActiveScene() noexcept;
		};

		template<SceneType T, class ...Args>
		inline Scene& SceneManager::add(const bool setItAsActiveScene, Args&& ...args)
		{
			Scene* const newScene = this->m_scenes.emplace_back(std::make_shared<T>(std::forward<Args>(args)...)).get();
			if (setItAsActiveScene)
				this->setActiveScene(*newScene);
			return *newScene;
		}
	}
}