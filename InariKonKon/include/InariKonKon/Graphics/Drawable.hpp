#pragma once

#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/RenderState.hpp"

namespace ikk
{
	class Window;

	template<Draw::Dimension D = Draw::Dimension::_3D>
	class Drawable
	{
	public:
		Drawable() noexcept = default;

		Drawable(const Drawable&) noexcept = default;
		Drawable(Drawable&&) noexcept = default;

		Drawable& operator=(const Drawable&) noexcept = default;
		Drawable& operator=(Drawable&&) noexcept = default;

		~Drawable() noexcept = default;

		virtual void draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept = 0;
		virtual void draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept = 0;
	protected:
		virtual void setup() noexcept = 0;

		//TODO:
		//Impl...
		//virtual void draw(type, usage, stb...)

		priv::VertexBufferObject m_VBO;
		priv::VertexArrayObject m_VAO;
		priv::ElementBufferObject m_EBO;
	};
}