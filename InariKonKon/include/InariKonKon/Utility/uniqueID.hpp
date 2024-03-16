#pragma once

#include <cstdint>

namespace ikk
{
	namespace priv
	{
		inline static std::uint32_t s_id = 0ULL;

		inline static const std::uint32_t getNextUniqueID() noexcept
		{
			return ++s_id;
		}
	}
}