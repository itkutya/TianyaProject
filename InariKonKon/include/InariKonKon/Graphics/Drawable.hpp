#pragma once

#include <cstdint>

#include "InariKonKon/Graphics/RenderState.hpp"

namespace ikk
{
	class Window;

	enum class Dimension : std::uint8_t
	{
		_GUI = 1, _2D, _3D
	};

	template<Dimension T = Dimension::_3D>
	class Drawable
	{
	public:
		enum class Usage : std::uint32_t
		{
			STREAM_DRAW = 0x88E0, STATIC_DRAW = 0x88E4, DYNAMIC_DRAW = 0x88E8
		};

		enum class Primitive : std::uint32_t
		{
			TRIANGLES = 0x0004
		};

		Drawable() noexcept = default;

		Drawable(const Drawable&) noexcept = default;
		Drawable(Drawable&&) noexcept = default;

		Drawable& operator=(const Drawable&) noexcept = default;
		Drawable& operator=(Drawable&&) noexcept = default;

		~Drawable() noexcept = default;

		virtual void draw(const Window& target, const RenderState& state) const noexcept = 0;
	};
}