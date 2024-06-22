module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module DrawEnums;

import <cstdint>;

class GLEnum
{
public:
	virtual constexpr ~GLEnum() = default;

	virtual constexpr operator std::uint32_t() const noexcept final { return this->value; };
protected:
	constexpr GLEnum(const std::uint32_t value) noexcept : value(value) {};

	std::uint32_t value;
};

export namespace ikk
{
	enum class Dimension : std::uint8_t
	{
		_GUI = 1, _2D, _3D
	};

	class Usage : public GLEnum
	{
	public:
		static const Usage None;
		static const Usage Stream;
		static const Usage Static;
		static const Usage Dynamic;
	private:
		constexpr Usage(const std::uint32_t value) noexcept : GLEnum(value) {};
	};

	inline constexpr Usage Usage::None(GL_NONE);
	inline constexpr Usage Usage::Stream(GL_STREAM_DRAW);
	inline constexpr Usage Usage::Static(GL_STATIC_DRAW);
	inline constexpr Usage Usage::Dynamic(GL_DYNAMIC_DRAW);

	class Primitive : public GLEnum
	{
	public:
		static const Primitive None;
		static const Primitive Triangles;
	private:
		constexpr Primitive(const std::uint32_t value) noexcept : GLEnum(value) {};
	};

	inline constexpr Primitive Primitive::None(GL_NONE);
	inline constexpr Primitive Primitive::Triangles(GL_TRIANGLES);

	class GLType : public GLEnum
	{
	public:
		static const GLType None;
		static const GLType Unsigned_Byte;
		static const GLType Unsigned_Short;
		static const GLType Unsigned_Int;
	private:
		constexpr GLType(const std::uint32_t value) noexcept : GLEnum(value) {};
	};

	inline constexpr GLType GLType::None(GL_NONE);
	inline constexpr GLType GLType::Unsigned_Byte(GL_UNSIGNED_BYTE);
	inline constexpr GLType GLType::Unsigned_Short(GL_UNSIGNED_SHORT);
	inline constexpr GLType GLType::Unsigned_Int(GL_UNSIGNED_INT);
}