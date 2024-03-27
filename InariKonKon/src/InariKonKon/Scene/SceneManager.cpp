#include "InariKonKon/Scene/SceneManager.hpp"

#include <cassert>

namespace ikk
{
	void SceneManager::processChanges() noexcept
	{
		if (this->m_pop && this->m_stack.size())
		{
			this->m_pop = false;
			this->m_stack.pop_back();
		}

		if (this->m_add)
		{
			if (this->m_replace && this->m_stack.size())
			{
				this->m_replace = false;
				this->m_stack.pop_back();
			}

			this->m_add = false;
			this->m_stack.emplace_back(std::move(this->m_newScene));
		}

		if (this->m_toBeRemoved.size() > 0)
		{
			for (const Scene::SceneID removedID : this->m_toBeRemoved)
				this->m_stack.erase(std::remove_if(this->m_stack.begin(), this->m_stack.end(), [removedID](const std::unique_ptr<Scene>& scene) { return scene->getID() == removedID; }));
			this->m_toBeRemoved.clear();
		}
	}

	void SceneManager::remove(const Scene::SceneID id) noexcept
	{
		this->m_toBeRemoved.emplace_back(id);
	}

	void SceneManager::pop(const std::size_t amount) noexcept
	{
		this->m_pop = true;
	}

	void SceneManager::clear() noexcept
	{
		this->m_stack.clear();
	}

	const std::size_t SceneManager::size() const noexcept
	{
		return this->m_stack.size();
	}

	const std::unique_ptr<Scene>& SceneManager::getActiveScene() const noexcept
	{
		assert(this->m_stack.size() > 0 && "No scene were added!");
		return this->m_stack.back();
	}
}