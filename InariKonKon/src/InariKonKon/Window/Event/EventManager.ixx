export module Window:EventManager;

import <queue>;

import Event;

namespace ikk
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

	const std::queue<Event>& EventManager::getEventQueue() const noexcept
	{
		return this->m_que;
	}

	std::queue<Event>& EventManager::getEventQueue() noexcept
	{
		return this->m_que;
	}
}