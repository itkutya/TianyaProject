#pragma once

#include <vector>
#include <memory>
#include <type_traits>
#include <utility>

#include "Scene.hpp"

template<class T, class U>
concept BaseOf = std::is_base_of<U, T>::value;

namespace ikk
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

		void processChanges() noexcept;

		template<BaseOf<Scene> T, class... Args>
		void add(const bool replace = false, Args&&... args) noexcept;
		void remove(const Scene::SceneID id) noexcept;
		void pop(const std::size_t amount = 1) noexcept;
		void clear() noexcept;

		const std::size_t size() const noexcept;

		const std::unique_ptr<Scene>& getActiveScene() const noexcept;
	private:
		std::vector<std::unique_ptr<Scene>> m_stack;
		std::vector<Scene::SceneID> m_toBeRemoved;
		std::unique_ptr<Scene> m_newScene;

		bool m_add = false;
		bool m_replace = false;
		bool m_pop = false;
	};

	template<BaseOf<Scene> T, class... Args>
	inline void SceneManager::add(const bool replace, Args&&... args) noexcept
	{
		this->m_add = true;
		this->m_replace = replace;
		if constexpr (sizeof...(args) > 0)
			this->m_newScene = std::make_unique<T>(std::forward<Args>(args)...);
		else
			this->m_newScene = std::make_unique<T>();
	}
}