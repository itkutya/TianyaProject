#pragma once

#include "InariKonKon/Utility/Math/Rect.hpp"
#include "InariKonKon/Graphics/RenderState.hpp"

import ElementBufferObject;
import VertexBufferObject;
import VertexArrayObject;

namespace ikk
{
	class Window;

	template<Dimension D = Dimension::_3D>
	class Drawable
	{
	public:
		Drawable() noexcept = default;

		Drawable(const Drawable<D>&) noexcept = default;
		Drawable(Drawable<D>&&) noexcept = default;

		Drawable<D>& operator=(const Drawable<D>&) noexcept = default;
		Drawable<D>& operator=(Drawable<D>&&) noexcept = default;

		~Drawable() noexcept = default;

		virtual void draw(const Window& target, RenderState<D, Projection::Ortho>& state) const noexcept = 0;
		virtual void draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept = 0;
	protected:
		VertexArrayObject m_VAO;
		VertexBufferObject m_VBO;
		ElementBufferObject m_EBO;

		virtual void preDraw(const Window& target, const RenderState<D, Projection::Ortho>& state, const FloatRect viewRect = { 1.f, 1.f, -1.f, -1.f }) const noexcept final;
		virtual void preDraw(const Window& target, const RenderState<D, Projection::Perspective>& state, const float aspectRatio) const noexcept final;
	};
}