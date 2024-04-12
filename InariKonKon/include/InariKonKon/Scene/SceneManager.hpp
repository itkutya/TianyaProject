#pragma once

#include <vector>
#include <memory>

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
			SceneManager(SceneManager&) noexcept = default;
			SceneManager(SceneManager&&) noexcept = default;

			SceneManager& operator=(const SceneManager&) noexcept = default;
			SceneManager& operator=(SceneManager&) noexcept = default;
			SceneManager& operator=(SceneManager&&) noexcept = default;

			~SceneManager() noexcept = default;

			template<SceneType T>
			Scene* const emplace(T&& scene, const bool setItAsActiveScene) noexcept;
			void remove(const Scene* scene, const bool resetActiveScene) noexcept;
			void pop(const bool resetActiveScene) noexcept;

			Scene* const setActiveScene(Scene* scene) noexcept;
			[[nodiscard]] const Scene* const getActiveScene() const noexcept;
			[[nodiscard]] Scene* const getActiveScene() noexcept;
		private:
			std::vector<std::unique_ptr<Scene>> m_scenes;
			Scene* m_activeScene = nullptr;
		};

		template<SceneType T>
		inline Scene* const SceneManager::emplace(T&& scene, const bool setItAsActiveScene) noexcept
		{
			Scene* const newScene = this->m_scenes.emplace_back<std::unique_ptr<T>>(std::make_unique<T>(std::move(scene))).get();
			if (setItAsActiveScene)
				this->m_activeScene = newScene;
			return newScene;
		}
	}
}