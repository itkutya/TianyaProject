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

		const priv::EntityComponentBase::EntityComponentID generateUniqueID() noexcept
		{
			static priv::EntityComponentBase::EntityComponentID s_id = 0;
			return ++s_id;
		}
	}
}