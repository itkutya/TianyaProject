#pragma once

#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Draw/RenderState.hpp"
#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"

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

		virtual void draw(const Window& window, RenderState<Projection::Ortho>& state) const noexcept = 0;
		virtual void draw(const Window& window, RenderState<Projection::Perspective>& state) const noexcept = 0;
	protected:
		priv::VertexArrayObject m_VAO;
		priv::VertexBufferObject m_VBO;
		priv::ElementBufferObject m_EBO;

		virtual void preDraw(const Window& window, RenderState<Projection::Ortho>& state, const FloatRect viewRect = { -1.f, -1.f, 1.f, 1.f }) const noexcept final;
		virtual void preDraw(const Window& window, RenderState<Projection::Perspective>& state, const float aspectRatio) const noexcept final;

		virtual void postDraw(const RenderState<Projection::Ortho>& state) const noexcept final;
		virtual void postDraw(const RenderState<Projection::Perspective>& state) const noexcept final;
	};

	template<Dimension D>
	void Drawable<D>::preDraw(const Window& window, RenderState<Projection::Ortho>& state, const FloatRect viewRect) const noexcept
	{
		if (state.shader == nullptr)
			state.shader = &Shader::getDefaultShaderProgram();

		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			//Check if shader has model in it...
			//state.shader->setMatrix4x4("model", state.transform->getMatrix());
			state.shader->setCamera(*state.camera, viewRect);
		}

		this->m_VAO.bind();
	}

	template<Dimension D>
	void Drawable<D>::preDraw(const Window& window, RenderState<Projection::Perspective>& state, const float aspectRatio) const noexcept
	{
		if (state.shader == nullptr)
			state.shader = &Shader::getDefaultShaderProgram();
		
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			//Check if shader has model in it...
			//state.shader->setMatrix4x4("model", state.transform->getMatrix());
			state.shader->setCamera(*state.camera, aspectRatio);
		}

		this->m_VAO.bind();
	}
	
	template<Dimension D>
	void Drawable<D>::postDraw(const RenderState<Projection::Ortho>& state) const noexcept
	{
		if (state.texture)
			state.texture->unbind();

		if (state.shader)
			state.shader->unbind();
	}

	template<Dimension D>
	void Drawable<D>::postDraw(const RenderState<Projection::Perspective>& state) const noexcept
	{
		if (state.texture)
			state.texture->unbind();

		if (state.shader)
			state.shader->unbind();
	}
}