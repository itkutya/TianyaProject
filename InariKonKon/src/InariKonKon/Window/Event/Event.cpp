#include "InariKonKon/Window/Event/Event.hpp"

namespace ikk
{
	Event::Event(const Event::Type type) noexcept : type(type), empty({})
	{
	}
}