#pragma once

#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/RenderState.hpp"

namespace ikk
{
	class Window;

	//TODO:
	//Make conversion from other types possible!
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

		virtual void draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept = 0;
		virtual void draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept = 0;

		virtual const Transform<D>& getTransform() const noexcept { return this->m_transfrom; };
		virtual Transform<D>& getTransform() noexcept { return this->m_transfrom; };
	protected:
		//VAO needs to store it's attributes & other stuff when we draw it with window it's gonna be easiear to draw...
		priv::VertexArrayObject m_VAO;
		priv::VertexBufferObject m_VBO;
		priv::ElementBufferObject m_EBO;

		Transform<D> m_transfrom{};
	};
}