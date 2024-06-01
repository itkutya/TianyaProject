#pragma once

#include <array>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Triangle final : public Drawable<D>
	{
	public:
		Triangle() noexcept;

		Triangle(const Triangle<D>&) noexcept = default;
		Triangle(Triangle<D>&&) noexcept = default;

		Triangle<D>& operator=(const Triangle<D>&) noexcept = default;
		Triangle<D>& operator=(Triangle<D>&&) noexcept = default;

		~Triangle() noexcept = default;

		void draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept override;

		[[nodiscard]] const std::array<Vertex, 3>& getVertices() const noexcept;
		[[nodiscard]] std::array<Vertex, 3>& getVertices() noexcept;
	private:
		std::array<Vertex, 3> m_vertices
		{
			Vertex({ -0.5f, -0.5f, 1.0f }, Color::Red, { 0.f, 0.f }),
			Vertex({  0.5f, -0.5f, 1.0f }, Color::Green, { 1.f, 0.f }),
			Vertex({  0.0f,  0.5f, 1.0f }, Color::Blue, { 0.5f, 1.f })
		};
	};

	using Triangle3D = Triangle<Dimension::_3D>;
	using Triangle2D = Triangle<Dimension::_2D>;
	using TriangleGUI = Triangle<Dimension::_GUI>;

	template<Dimension D>
	inline Triangle<D>::Triangle() noexcept
	{
		this->m_VAO.bind();
		this->m_VBO.BufferData(std::span{ this->m_vertices });
		this->m_VAO.setupVertexAttributes();
	}

	template<Dimension D>
	inline void Triangle<D>::draw(const Window& target, const RenderState<D, Projection::Orhto>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			if (state.transform)
				state.shader->setMatrix4x4("model", state.transform->getMatrix());
			else
				state.shader->setMatrix4x4("model", this->getTransform().getMatrix());

			state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
			state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(2.f, 2.f, -2.f, -2.f));
		}

		this->m_VAO.bind();
		target.draw(Primitive::Triangles, 3, 0);
	}

	template<Dimension D>
	inline void Triangle<D>::draw(const Window& target, const RenderState<D, Projection::Perspective>& state) const noexcept
	{
		state.shader->bind();

		if (state.texture)
			state.texture->bind();

		if (state.camera != nullptr)
		{
			mat4x4 model(1.f);
			state.shader->setMatrix4x4("model", model);
			state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
			state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(target.getAspectRatio()));
		}

		this->m_VAO.bind();
		target.draw(Primitive::Triangles, 3, 0);
	}

	template<Dimension D>
	inline const std::array<Vertex, 3>& Triangle<D>::getVertices() const noexcept
	{
		return this->m_vertices;
	}

	template<Dimension D>
	inline std::array<Vertex, 3>& Triangle<D>::getVertices() noexcept
	{
		return this->m_vertices;
	}
}