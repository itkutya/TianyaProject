#pragma once

#include "InariKonKon/Graphics/RenderState.hpp"
#include "InariKonKon/Graphics/DrawOptions.hpp"

namespace ikk
{
	class Window;

	template<Draw::Dimension T = Draw::Dimension::_3D>
	class Drawable
	{
	public:
		Drawable() noexcept = default;

		Drawable(const Drawable&) noexcept = default;
		Drawable(Drawable&&) noexcept = default;

		Drawable& operator=(const Drawable&) noexcept = default;
		Drawable& operator=(Drawable&&) noexcept = default;

		~Drawable() noexcept = default;

		virtual void draw(const Window& target, const RenderState& state) const noexcept = 0;
	};
}