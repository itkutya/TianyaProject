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

	namespace priv
	{
		class GLEnum
		{
		public:
			virtual constexpr ~GLEnum() = default;

			virtual constexpr operator std::uint32_t() const noexcept final { return this->value; };
		protected:
			constexpr GLEnum(const std::uint32_t value) noexcept : value(value) {};

			std::uint32_t value;
		};
	}

	class Usage : public priv::GLEnum
	{
	public:
		static const Usage None;
		static const Usage Stream;
		static const Usage Static;
		static const Usage Dynamic;
	private:
		constexpr Usage(const std::uint32_t value) noexcept : GLEnum(value) {};
	};

	inline constexpr Usage Usage::None(0x0);
	inline constexpr Usage Usage::Stream(0x88E0);
	inline constexpr Usage Usage::Static(0x88E4);
	inline constexpr Usage Usage::Dynamic(0x88E8);

	class Primitive : public priv::GLEnum
	{
	public:
		static const Primitive None;
		static const Primitive Triangles;
	private:
		constexpr Primitive(const std::uint32_t value) noexcept : GLEnum(value) {};
	};

	inline constexpr Primitive Primitive::None(0x0);
	inline constexpr Primitive Primitive::Triangles(0x0004);

	class GLType : public priv::GLEnum
	{
	public:
		static const GLType None;
		static const GLType Unsigned_Byte;
		static const GLType Unsigned_Short;
		static const GLType Unsigned_Int;
	private:
		constexpr GLType(const std::uint32_t value) noexcept : GLEnum(value) {};
	};

	inline constexpr GLType GLType::None(0x0);
	inline constexpr GLType GLType::Unsigned_Byte(0x1401);
	inline constexpr GLType GLType::Unsigned_Short(0x1403);
	inline constexpr GLType GLType::Unsigned_Int(0x1405);
}