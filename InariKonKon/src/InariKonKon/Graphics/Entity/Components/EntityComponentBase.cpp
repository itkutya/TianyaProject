#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"

namespace ikk
{
	namespace priv
	{
		const priv::EntityComponentBase::EntityComponentID generateUniqueID() noexcept
		{
			static priv::EntityComponentBase::EntityComponentID s_id = 0;
			return ++s_id;
		}
	}
}