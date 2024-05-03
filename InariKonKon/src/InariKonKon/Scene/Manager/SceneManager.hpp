#pragma once

#include <vector>

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

			Scene* const emplace(std::unique_ptr<Scene>&& scene, const bool setItAsActiveScene) noexcept;
			void remove(const Scene* scene, const bool resetActiveScene) noexcept;
			void pop(const bool resetActiveScene) noexcept;

			Scene* const setActiveScene(Scene* scene) noexcept;
			[[nodiscard]] const Scene* const getActiveScene() const noexcept;
			[[nodiscard]] Scene* const getActiveScene() noexcept;
		private:
			std::vector<std::unique_ptr<Scene>> m_scenes;
			Scene* m_activeScene = nullptr;
		};
	}
}