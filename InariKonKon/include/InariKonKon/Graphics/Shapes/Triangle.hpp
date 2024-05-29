#pragma once

#include <array>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

namespace ikk
{
	class Triangle final : public Drawable<Draw::Dimension::_2D>
	{
	public:
		Triangle() noexcept;

		Triangle(const Triangle&) noexcept = default;
		Triangle(Triangle&&) noexcept = default;

		Triangle& operator=(const Triangle&) noexcept = default;
		Triangle& operator=(Triangle&&) noexcept = default;

		~Triangle() noexcept = default;

		void draw(const Window& target, const RenderState<Draw::Dimension::_2D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, const RenderState<Draw::Dimension::_2D, Projection::Perspective>& state) const noexcept override;
	private:
		std::array<Vertex, 3> m_vertices
		{
			Vertex({ -0.5f, -0.5f, 1.0f }, Color::Red, { 0.f, 0.f }),
			Vertex({  0.5f, -0.5f, 1.0f }, Color::Green, { 1.f, 0.f }),
			Vertex({  0.0f,  0.5f, 1.0f }, Color::Blue, { 0.5f, 1.f })
		};

		void setup() noexcept override;
	};
}