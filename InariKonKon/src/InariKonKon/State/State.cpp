#include "InariKonKon/State/State.hpp"

#include "InariKonKon/Utility/uniqueID.hpp"

namespace ikk
{
	State::State() noexcept : m_id(priv::getNextUniqueID())
	{
	}

	const std::uint32_t& State::getID() const noexcept
	{
		return this->m_id;
	}
}