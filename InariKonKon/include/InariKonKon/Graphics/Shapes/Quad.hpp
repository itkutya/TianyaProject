#pragma once

#include <array>

#include "InariKonKon/Graphics/Drawable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"

#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

namespace ikk
{
	class Quad final : public Drawable<Dimension::_2D>
	{
	public:
		Quad(const Color c = Color::White) noexcept;

		Quad(const Quad&) noexcept = default;
		Quad(Quad&&) noexcept = default;

		Quad& operator=(const Quad&) noexcept = default;
		Quad& operator=(Quad&&) noexcept = default;

		~Quad() noexcept = default;
	private:
		std::array<Vertex, 4> m_vertices
		{
			Vertex({  1.f,  1.f, 0.0f }, Color::White, { 1.f, 1.f }),
			Vertex({  1.f, -1.f, 0.0f }, Color::White, { 1.f, 0.f }),
			Vertex({ -1.f, -1.f, 0.0f }, Color::White, { 0.f, 0.f }),
			Vertex({ -1.f,  1.f, 0.0f }, Color::White, { 0.f, 1.f })
		};

		std::array<std::uint32_t, 6> m_indices
		{
			0, 1, 3,
			1, 2, 3
		};

		priv::VertexBufferObject VBO;
		priv::VertexArrayObject VAO;
		priv::ElementBufferObject EBO;

		void draw(const Window& target, const RenderState& state) noexcept override;
	};
}