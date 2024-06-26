#pragma once

#include <queue>

#include "InariKonKon/Window/Event/Event.hpp"

namespace ikk
{
	namespace priv
	{
		class EventManager final
		{
		public:
			EventManager() noexcept = default;

			EventManager(const EventManager&) noexcept = default;
			EventManager(EventManager&&) noexcept = default;

			EventManager& operator=(const EventManager&) noexcept = default;
			EventManager& operator=(EventManager&&) noexcept = default;

			~EventManager() noexcept = default;

			[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
			[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;
		private:
			std::queue<Event> m_que;
		};
	}
}