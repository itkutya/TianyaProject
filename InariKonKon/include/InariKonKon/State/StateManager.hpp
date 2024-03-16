#pragma once

#include <memory>
#include <vector>
#include <type_traits>
#include <utility>

#include "State.hpp"

template<class T, class U>
concept BaseOf = std::is_base_of<U, T>::value;

namespace ikk
{
	class StateManager final
	{
	public:
		StateManager() noexcept = default;

		StateManager(const StateManager&) noexcept = default;
		StateManager(StateManager&) noexcept = default;
		StateManager(StateManager&&) noexcept = default;

		StateManager& operator=(const StateManager&) noexcept = default;
		StateManager& operator=(StateManager&) noexcept = default;
		StateManager& operator=(StateManager&&) noexcept = default;

		~StateManager() noexcept = default;

		void processChanges() noexcept;

		template<BaseOf<State> T, class... Args>
		void add(const bool replaceAll = false, Args... args) noexcept;
		void remove(const std::uint32_t id) noexcept;
		void pop(const std::size_t amount = 1) noexcept;
		void clear() noexcept;

		const std::vector<std::unique_ptr<State>>& getActiveStates() const noexcept;
	private:
		std::vector<std::unique_ptr<State>> m_states;
		std::vector<std::uint32_t> m_toBeRemoved;
	};

	template<BaseOf<State> T, class ...Args>
	inline void StateManager::add(const bool replaceAll, Args ...args) noexcept
	{
		if constexpr (sizeof...(args) > 0)
		{
			if (replaceAll)
				this->clear();
			this->m_states.emplace_back<std::unique_ptr<T>>(std::make_unique<T>(std::forward<Args>(args)...));
		}
		else
		{
			if (replaceAll)
				this->clear();
			this->m_states.emplace_back<std::unique_ptr<T>>(std::make_unique<T>());
		}
	}
}