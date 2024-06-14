export module Drawable;

export import RenderState;

import VertexArrayObject;
import VertexBufferObject;
import ElementBufferObject;

export namespace ikk
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

		virtual void preDraw(const Window& target, const RenderState<D, Projection::Ortho>& state) const noexcept final
		{
			state.shader->bind();

			if (state.texture)
				state.texture->bind();

			if (state.camera != nullptr)
			{
				//Check if shader has model in it...
				state.shader->setMatrix4x4("model", state.transform->getMatrix());
				state.shader->setCamera(target, *state.camera);
			}

			this->m_VAO.bind();
		};

		virtual void preDraw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept final
		{
			state.shader->bind();

			if (state.texture)
				state.texture->bind();

			if (state.camera != nullptr)
			{
				//Check if shader has model in it...
				state.shader->setMatrix4x4("model", state.transform->getMatrix());
				state.shader->setCamera(target, *state.camera);
			}

			this->m_VAO.bind();
		};
	};
}