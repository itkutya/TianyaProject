#pragma once

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"

namespace ikk
{
	struct Glyph
	{
		FloatRect bounds = { 0.f, 0.f, 0.f, 0.f };
		vec2f bearing = { 0.f, 0.f };
		vec2u advance = { 0u, 0u };
		std::uint32_t width = 0u;
		std::uint32_t height = 0u;
	};
}