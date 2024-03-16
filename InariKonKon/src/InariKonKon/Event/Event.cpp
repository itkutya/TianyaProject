#include "InariKonKon/Event/Event.hpp"

namespace ikk
{
	Event::Event(const Type type) noexcept : m_type(type)
	{
	}

	const Event::Type& Event::getType() const noexcept
	{
		return this->m_type;
	}
}