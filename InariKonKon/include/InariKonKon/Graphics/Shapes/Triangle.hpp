#pragma once

#include <array>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

namespace ikk
{
	template<Draw::Dimension D = Draw::Dimension::_2D>
	class Triangle final : public Drawable<D>
	{
	public:
		Triangle() noexcept;

		Triangle(const Triangle&) noexcept = default;
		Triangle(Triangle&&) noexcept = default;

		Triangle& operator=(const Triangle&) noexcept = default;
		Triangle& operator=(Triangle&&) noexcept = default;

		~Triangle() noexcept = default;

		void draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept override;
	private:
		std::array<Vertex, 3> m_vertices
		{
			Vertex({ -0.5f, -0.5f, 1.0f }, Color::Red, { 0.f, 0.f }),
			Vertex({  0.5f, -0.5f, 1.0f }, Color::Green, { 1.f, 0.f }),
			Vertex({  0.0f,  0.5f, 1.0f }, Color::Blue, { 0.5f, 1.f })
		};

		void setup() noexcept override;
	};

	template<Draw::Dimension D>
	inline Triangle<D>::Triangle() noexcept
	{
		this->setup();
	}

	template<Draw::Dimension D>
	inline void Triangle<D>::draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			mat4x4 model(1.f);
			state.shader->setMatrix4x4("model", model);
			state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
			//state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix());
		}

		this->m_VAO.bind();
		//gl->Enable(GL_DEPTH_TEST);
		//gl->DrawArrays(GL_TRIANGLES, 0, 3);
	}

	template<Draw::Dimension D>
	inline void Triangle<D>::draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			mat4x4 model(1.f);
			state.shader->setMatrix4x4("model", model);
			//Shader set camera class...
			//state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
			//state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(target.getAspectRatio()));
		}

		this->m_VAO.bind();
		//Do this in the window draw func...
		//gl->Enable(GL_DEPTH_TEST);
		//gl->DrawArrays(GL_TRIANGLES, 0, 3);
	}

	template<Draw::Dimension D>
	inline void Triangle<D>::setup() noexcept
	{
		this->m_VAO.bind();
		this->m_VBO.BufferData(std::span{ this->m_vertices });
		this->m_VAO.setupVertexAttributes();
	}
}