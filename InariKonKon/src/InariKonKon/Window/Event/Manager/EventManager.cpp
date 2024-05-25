#include "InariKonKon/Window/Event/Manager/EventManager.hpp"

const std::queue<ikk::Event>& ikk::priv::EventManager::getEventQueue() const noexcept
{
	return this->m_que;
}

std::queue<ikk::Event>& ikk::priv::EventManager::getEventQueue() noexcept
{
	return this->m_que;
}