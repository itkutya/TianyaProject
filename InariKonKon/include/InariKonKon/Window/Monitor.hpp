#pragma once

#include <cstdint>

#include "InariKonKon/Utility/Math/Vector2.hpp"

namespace ikk
{
	struct Monitor final
	{
		Monitor() noexcept = default;
		Monitor(const std::uint32_t width, const std::uint32_t height) noexcept;

		Monitor(const Monitor&) noexcept = default;
		Monitor(Monitor&&) noexcept = default;

		Monitor& operator=(const Monitor&) noexcept = default;
		Monitor& operator=(Monitor&&) noexcept = default;

		~Monitor() noexcept = default;

		vec2u size = { 0, 0 };
		//TODO:
		//Monitor support...
	};
}