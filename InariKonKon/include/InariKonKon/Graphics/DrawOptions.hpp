#pragma once

#include <cstdint>

namespace ikk
{
	namespace Draw
	{
		enum class Dimension : std::uint8_t
		{
			_GUI = 1, _2D, _3D
		};

		enum class Usage : std::uint32_t
		{
			Stream = 0x88E0, Static = 0x88E4, Dynamic = 0x88E8
		};

		enum class Primitive : std::uint32_t
		{
			Triangles = 0x0004
		};
	}

	namespace priv
	{
		class GLType
		{
		public:
			constexpr operator std::uint32_t() const noexcept { return this->value; };

			static const GLType None;
			static const GLType Unsigned_Byte;
			static const GLType Unsigned_Short;
			static const GLType Unsigned_Int;
		private:
			constexpr GLType(const std::uint32_t value) noexcept : value(value) {};

			std::uint32_t value;
		};

		inline constexpr GLType GLType::None(0x0000);
		inline constexpr GLType GLType::Unsigned_Byte(0x1401);
		inline constexpr GLType GLType::Unsigned_Short(0x1403);
		inline constexpr GLType GLType::Unsigned_Int(0x1405);
	}
}