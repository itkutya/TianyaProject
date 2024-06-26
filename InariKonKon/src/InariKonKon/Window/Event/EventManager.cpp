#include "InariKonKon/Window/Event/EventManager.hpp"

namespace ikk
{
	namespace priv
	{
		const std::queue<Event>& EventManager::getEventQueue() const noexcept
		{
			return this->m_que;
		}

		std::queue<Event>& EventManager::getEventQueue() noexcept
		{
			return this->m_que;
		}
	}
}