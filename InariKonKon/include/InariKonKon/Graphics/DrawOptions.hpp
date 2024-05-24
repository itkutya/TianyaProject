#pragma once

namespace ikk
{
	namespace Draw
	{
		enum class Dimension : std::uint8_t
		{
			_GUI = 1, _2D, _3D
		};

		enum Usage : std::uint32_t
		{
			STREAM_DRAW = 0x88E0, STATIC_DRAW = 0x88E4, DYNAMIC_DRAW = 0x88E8
		};

		enum Primitive : std::uint32_t
		{
			Triangles = 0x0004
		};
	}

	namespace priv
	{
		enum GLType : std::uint32_t
		{
			NONE = 0x0000, UNSIGNED_BYTE = 0x1401, UNSIGNED_SHORT = 0x1403, UNSIGNED_INT = 0x1405
		};
	}
}