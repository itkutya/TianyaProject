module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module Quad;

import <array>;

export import Transformable;
export import Drawable;
export import Vertex;
export import Window;

import Context;
import VertexArrayObject;
import VertexBufferObject;
import ElementBufferObject;

export namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Quad final : public Drawable<D>, public Transformable<D>
	{
	public:
		Quad(const Color c = Color::White) noexcept;

		Quad(const Quad<D>&) noexcept = default;
		Quad(Quad<D>&&) noexcept = default;

		Quad<D>& operator=(const Quad<D>&) noexcept = default;
		Quad<D>& operator=(Quad<D>&&) noexcept = default;

		~Quad() noexcept = default;

		void draw(const Window& target, RenderState<D, Projection::Ortho>& state) const noexcept override;
		void draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept override;

		[[nodiscard]] const std::array<Vertex, 4>& getVertices() const noexcept;
		[[nodiscard]] std::array<Vertex, 4>& getVertices() noexcept;
	private:
		std::array<Vertex, 4> m_vertices =
		{
			Vertex({  1.f,  1.f, 0.0f }, Color::White, { 1.f, 1.f }),
			Vertex({  1.f, -1.f, 0.0f }, Color::White, { 1.f, 0.f }),
			Vertex({ -1.f, -1.f, 0.0f }, Color::White, { 0.f, 0.f }),
			Vertex({ -1.f,  1.f, 0.0f }, Color::White, { 0.f, 1.f })
		};

		std::array<std::uint8_t, 6> m_indices
		{
			0, 1, 3,
			1, 2, 3
		};
	};

	using Quad3D = Quad<Dimension::_3D>;
	using Quad2D = Quad<Dimension::_2D>;
	using QuadGUI = Quad<Dimension::_GUI>;

	template<Dimension D>
	Quad<D>::Quad(const Color c) noexcept
	{
		for (Vertex& vertex : this->m_vertices)
			vertex.color = c;

		this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices }, this->m_EBO, std::span{ this->m_indices });
	}

	template<Dimension D>
	void Quad<D>::draw(const Window& target, RenderState<D, Projection::Ortho>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(target, state);
		//gl->Enable(GL_DEPTH_TEST);
		//gl->DepthFunc(GL_ALWAYS);
		gl->DrawElements(Primitive::Triangles, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
	}

	template<Dimension D>
	void Quad<D>::draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(target, state);
		//gl->Enable(GL_DEPTH_TEST);
		//gl->DepthFunc(GL_ALWAYS);
		gl->DrawElements(Primitive::Triangles, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
	}

	template<Dimension D>
	const std::array<Vertex, 4>& Quad<D>::getVertices() const noexcept
	{
		return this->m_vertices;
	}

	template<Dimension D>
	std::array<Vertex, 4>& Quad<D>::getVertices() noexcept
	{
		return this->m_vertices;
	}
}