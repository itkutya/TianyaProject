#pragma once

#include <cstdint>

namespace ikk
{
	enum class Dimension : std::uint8_t
	{
		_UI = 1, _2D = 2, _3D = 3
	};

	enum class Projection : std::uint8_t
	{
		None = 0, Ortho = 1, Perspective = 2
	};
}