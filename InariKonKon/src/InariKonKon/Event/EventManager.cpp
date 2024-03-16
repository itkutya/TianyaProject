#include "InariKonKon/Event/EventManager.hpp"

namespace ikk
{
	namespace priv
	{
		void EventManager::insert(const Event& event) noexcept
		{
			this->m_queue.emplace(event);
		}

		const std::queue<Event>& EventManager::getEventQueue() const noexcept
		{
			return this->m_queue;
		}
		std::queue<Event>& EventManager::getEventQueue() noexcept
		{
			return this->m_queue;
		}
	}
}