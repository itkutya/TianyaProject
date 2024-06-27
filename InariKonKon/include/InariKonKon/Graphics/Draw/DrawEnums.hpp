#pragma once

#include <cstdint>

namespace ikk
{
	enum class Dimension : std::uint8_t
	{
		_GUI = 1, _2D = 2, _3D = 3
	};

	enum class Projection : std::uint8_t
	{
		Ortho = 0, Perspective = 1
	};
}