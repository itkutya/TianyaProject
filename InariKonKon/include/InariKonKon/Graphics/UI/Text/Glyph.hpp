#pragma once

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"

namespace ikk
{
	struct Glyph
	{
		FloatRect bounds = { 0.f, 0.f, 0.f, 0.f };
		vec2u bearing = { 0, 0 };
		vec2u origin = { 0, 0 };
		std::uint32_t width = 0;
		std::uint32_t height = 0;
		std::uint32_t advance = 0;
	};
}