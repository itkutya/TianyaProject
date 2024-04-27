#pragma once

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	class Triangle final : public Drawable
	{
	public:
		Triangle() noexcept;

		Triangle(const Triangle&) noexcept = default;
		Triangle(Triangle&&) noexcept = default;

		Triangle& operator=(const Triangle&) noexcept = default;
		Triangle& operator=(Triangle&&) noexcept = default;

		~Triangle() noexcept = default;
	private:
		Vertex m_vertices[3]{
								Vertex({ -0.5f, -0.5f, 0.0f }, Color::Red),
								Vertex({  0.5f, -0.5f, 0.0f }, Color::Green),
								Vertex({  0.0f,  0.5f, 0.0f }, Color::Blue)
							};

		priv::VertexBufferObject VBO;
		priv::VertexArrayObject VAO;
		
		void draw(const Window& target) noexcept override;
	};
}