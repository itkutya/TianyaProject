#pragma once

#include <array>

#include "InariKonKon/Graphics/Drawable/Drawable.hpp"
#include "InariKonKon/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Triangle final : public Drawable, public Transformable<D>
	{
	public:
		Triangle(const vec3f pos = { 0.f, 0.f, 0.f }, const vec2f size = { 1.f, 1.f }, const Color color = Color::White, const FloatRect textureRect = { 0.f, 0.f, 1.f, 1.f }) noexcept;

		Triangle(const Triangle<D>&) noexcept = default;
		Triangle(Triangle<D>&&) noexcept = default;

		Triangle<D>& operator=(const Triangle<D>&) noexcept = default;
		Triangle<D>& operator=(Triangle<D>&&) noexcept = default;

		~Triangle() noexcept = default;

		[[nodiscard]] const std::array<Vertex, 3>& getVertices() const noexcept;
		[[nodiscard]] std::array<Vertex, 3>& getVertices() noexcept;

		void draw() const noexcept override;
	private:
		std::array<Vertex, 3> m_vertices =
		{
			Vertex({ -0.5f, -0.5f, 0.f }, Color::White, { 0.f,  0.f }),
			Vertex({  0.5f, -0.5f, 0.f }, Color::White, { 1.f,  0.f }),
			Vertex({  0.f,   0.5f, 0.f }, Color::White, { 0.5f, 1.f })
		};
	};

	using Triangle3D = Triangle<Dimension::_3D>;
	using Triangle2D = Triangle<Dimension::_2D>;
	using TriangleGUI = Triangle<Dimension::_UI>;

	template<Dimension D>
	Triangle<D>::Triangle(const vec3f pos, const vec2f size, const Color color, const FloatRect textureRect) noexcept : Transformable<D>(pos, size)
	{
		for (Vertex& vertex : this->m_vertices)
			vertex.color = color;

		//TODO:
		//Texture coords...

		this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices });
	}

	template<Dimension D>
	const std::array<Vertex, 3>& Triangle<D>::getVertices() const noexcept
	{
		return this->m_vertices;
	}

	template<Dimension D>
	std::array<Vertex, 3>& Triangle<D>::getVertices() noexcept
	{
		return this->m_vertices;
	}

	template<Dimension D>
	void Triangle<D>::draw() const noexcept
	{
		gl->DrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(this->m_vertices.size()));
	}
}