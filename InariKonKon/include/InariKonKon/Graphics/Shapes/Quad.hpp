#pragma once

#include <array>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

namespace ikk
{
	class Quad final : public Drawable<Draw::Dimension::_2D>
	{
	public:
		Quad(const Color c = Color::White) noexcept;

		Quad(const Quad&) noexcept = default;
		Quad(Quad&&) noexcept = default;

		Quad& operator=(const Quad&) noexcept = default;
		Quad& operator=(Quad&&) noexcept = default;

		~Quad() noexcept = default;

		void draw(const Window& target, const RenderState<Draw::Dimension::_2D, Projection::Orhto>& state) const noexcept override;
		void draw(const Window& target, const RenderState<Draw::Dimension::_2D, Projection::Perspective>& state) const noexcept override;
	private:
		std::array<Vertex, 4> m_vertices
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

		void setup() noexcept override;
	};
}