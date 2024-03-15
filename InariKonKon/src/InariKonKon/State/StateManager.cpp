#include "InariKonKon/State/StateManager.hpp"

namespace ikk
{
	void StateManager::processChanges() noexcept
	{
		if (this->m_toBeRemoved.size() > 0)
		{
			for (const auto removedID : this->m_toBeRemoved)
				this->m_states.erase(std::remove_if(this->m_states.begin(), this->m_states.end(), [removedID](const std::unique_ptr<State>& state) { return state->getID() == removedID; }));
			this->m_toBeRemoved.clear();
		}
	}

	void StateManager::remove(const std::uint32_t id) noexcept
	{
		this->m_toBeRemoved.emplace_back(id);
	}

	void StateManager::pop(const std::size_t amount) noexcept
	{
		for (std::size_t i = 0; i < amount; ++i)
			if (i < this->m_states.size())
				this->m_toBeRemoved.emplace_back((*(this->m_states.end() - (i + 1)))->getID());
			else
				return;
	}

	void StateManager::clear() noexcept
	{
		this->pop(this->m_states.size());
	}

	const std::vector<std::unique_ptr<State>>& ikk::StateManager::getActiveStates() const noexcept
	{
		return this->m_states;
	}
}