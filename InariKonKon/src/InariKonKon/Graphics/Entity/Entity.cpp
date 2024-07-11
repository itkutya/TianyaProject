#include "InariKonKon/Entity/Entity.hpp"

namespace ikk
{
	inline static Entity::EntityID s_uniqueID = 0;

	Entity::Entity() noexcept : m_id(++s_uniqueID)
	{
	}

	const bool Entity::operator==(const Entity& other) const noexcept
	{
		return this->getID() == other.getID();
	}

	const Entity::EntityID& Entity::getID() const noexcept
	{
		return this->m_id;
	}
}