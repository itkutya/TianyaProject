#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"

namespace ikk
{
	EntityComponentBase::EntityComponentBase(const EntityComponentID id) noexcept : m_id(id)
	{
	}

	const bool EntityComponentBase::operator==(const EntityComponentBase& other) const noexcept
	{
		return this->getID() == other.getID();
	}

	const EntityComponentBase::EntityComponentID& EntityComponentBase::getID() const noexcept
	{
		return this->m_id;
	}
}