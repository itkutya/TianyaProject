#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"

namespace ikk
{
	namespace priv
	{
		EntityComponentBase::EntityComponentBase(const EntityComponentBase::EntityComponentID id) noexcept : m_id(id)
		{
		}

		const EntityComponentBase::EntityComponentID& EntityComponentBase::getID() const noexcept
		{
			return this->m_id;
		}
	}
}