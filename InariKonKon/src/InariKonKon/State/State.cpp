#include "InariKonKon/State/State.hpp"

#include <random>
#include <limits>

inline static auto getRandomID = []()
{
	std::random_device r;
	std::default_random_engine e(r());
	std::uniform_int_distribution<std::uint32_t> uniform_dist(std::numeric_limits<std::uint32_t>::min(), std::numeric_limits<std::uint32_t>::max());
	return uniform_dist(e);
};

namespace ikk
{
	State::State() noexcept : m_id(getRandomID())
	{
	}

	const std::uint32_t& State::getID() const noexcept
	{
		return this->m_id;
	}
}