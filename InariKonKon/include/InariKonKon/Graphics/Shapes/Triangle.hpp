#pragma once

#include <array>

#include "InariKonKon/Graphics/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"
#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Triangle final : public Drawable<D>, public Transformable<D>
	{
	public:
		Triangle() noexcept;

		Triangle(const Triangle<D>&) noexcept = default;
		Triangle(Triangle<D>&&) noexcept = default;

		Triangle<D>& operator=(const Triangle<D>&) noexcept = default;
		Triangle<D>& operator=(Triangle<D>&&) noexcept = default;

		~Triangle() noexcept = default;

		void draw(const Window& target, RenderState<D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept override;

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
		this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices });
	}

	template<Dimension D>
	inline void Triangle<D>::draw(const Window& target, RenderState<D, Projection::Orhto>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(target, state);
		target.draw(Primitive::Triangles, 3, 0);
	}

	template<Dimension D>
	inline void Triangle<D>::draw(const Window& target, RenderState<D, Projection::Perspective>& state) const noexcept
	{
		if (state.transform == nullptr)
			state.transform = &this->getTransform();

		this->preDraw(target, state);
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