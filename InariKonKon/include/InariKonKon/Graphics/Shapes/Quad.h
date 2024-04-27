#pragma once

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

#include "InariKonKon/Graphics/Shader/Shader.hpp"

#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

namespace ikk
{
	class Quad final : public Drawable
	{
	public:
		Quad() noexcept;

		Quad(const Quad&) noexcept = default;
		Quad(Quad&&) noexcept = default;

		Quad& operator=(const Quad&) noexcept = default;
		Quad& operator=(Quad&&) noexcept = default;

		~Quad() noexcept = default;
	private:
		Vertex m_vertices[4]
		{
			Vertex({  1.f,  1.f, 0.0f }, Color::White, { 0.f, 1.f }),
			Vertex({  1.f, -1.f, 0.0f }, Color::White, { 1.f, 1.f }),
			Vertex({ -1.f, -1.f, 0.0f }, Color::White, { 1.f, 0.f }),
			Vertex({ -1.f,  1.f, 0.0f }, Color::White, { 0.f, 0.f })
		};

		std::uint32_t m_indices[6]
		{
			0, 1, 3,
			1, 2, 3
		};

		priv::VertexBufferObject VBO;
		priv::VertexArrayObject VAO;
		priv::ElementBufferObject EBO;

		void draw(const Window& target) noexcept override;
	};
}