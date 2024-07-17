#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

#include "InariKonKon/Application/Scene/Scene.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
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
		Scene& add(T&& scene, const bool setItAsActiveScene = true);
		void remove(const Scene& scene, const bool resetActiveScene = true) noexcept;

		Scene& setActiveScene(Scene& scene) noexcept;

		[[nodiscard]] const Scene& getActiveScene() const noexcept;
		[[nodiscard]] Scene& getActiveScene() noexcept;
	private:
		std::unordered_map<Scene::SceneID, std::shared_ptr<Scene>> m_scenes;
		Scene* m_activeScene = nullptr;

		std::vector<std::shared_ptr<Scene>> m_newScenes;
		std::vector<Scene::SceneID> m_removedScenes;

		void resetActiveScene() noexcept;

		friend class Application;
		void handleSceneChanges() noexcept;

		void dispatchEvent(const Event& event) noexcept;
		void update(const Time& dt) noexcept;
		void render(const Window& window) const noexcept;
	};

	template<SceneType T>
	Scene& SceneManager::add(T&& scene, const bool setItAsActiveScene)
	{
		Scene& newScene = *this->m_newScenes.emplace_back(std::make_shared<T>(std::move(scene))).get();
		if (setItAsActiveScene)
			this->setActiveScene(newScene);
		return newScene;
	}
}