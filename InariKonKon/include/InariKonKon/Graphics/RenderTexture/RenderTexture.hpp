#pragma once

#include <array>

#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	class RenderTexture
	{
	public:
		RenderTexture(const Vector2<std::uint32_t> screenSize) noexcept;

		RenderTexture(const RenderTexture&) noexcept = default;
		RenderTexture(RenderTexture&&) noexcept = default;

		virtual RenderTexture& operator=(const RenderTexture&) noexcept = default;
		virtual RenderTexture& operator=(RenderTexture&&) noexcept = default;

		virtual ~RenderTexture() noexcept = default;

		[[nodiscard]] virtual const	priv::FrameBuffer& getFrameBuffer() const	noexcept final;
		[[nodiscard]] virtual		priv::FrameBuffer& getFrameBuffer()			noexcept final;

		virtual void draw(const Shader& shader, const Texture& texture) const noexcept final;
	private:
		priv::VertexArrayObject m_VAO;
		priv::VertexBufferObject m_VBO;
		priv::ElementBufferObject m_EBO;

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

		priv::FrameBuffer m_buffer;
	};
}