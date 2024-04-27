#pragma once

#include <cstdint>

#include "InariKonKon/Graphics/RenderState.hpp"

namespace ikk
{
	class Window;

	class Drawable
	{
	public:
		enum class Type : std::uint32_t
		{
			STREAM_DRAW = 0x88E0, STATIC_DRAW = 0x88E4, DYNAMIC_DRAW = 0x88E8
		};

		Drawable() noexcept = default;

		Drawable(const Drawable&) noexcept = default;
		Drawable(Drawable&&) noexcept = default;

		Drawable& operator=(const Drawable&) noexcept = default;
		Drawable& operator=(Drawable&&) noexcept = default;

		~Drawable() noexcept = default;
	protected:
		friend class Window;

		virtual void draw(const Window& target, const RenderState& state) noexcept = 0;
	};
}