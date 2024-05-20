#pragma once

#include <array>

#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"
#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/RenderState.hpp"

namespace ikk
{
	class Window;

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

		virtual void display(const Window& window, const RenderState& state) const noexcept final;
	protected:
	private:
		std::array<float, 16> m_vertices
		{
		//	 Position	TexCoord
			 1.f,  1.f, 1.f, 1.f,
			 1.f, -1.f, 1.f, 0.f,
			-1.f, -1.f, 0.f, 0.f,
			-1.f,  1.f, 0.f, 1.f
		};

		std::array<std::uint32_t, 6> m_indices
		{
			0, 1, 3,
			1, 2, 3
		};

		priv::VertexBufferObject VBO;
		priv::VertexArrayObject VAO;
		priv::ElementBufferObject EBO;

		priv::FrameBuffer m_buffer;
	};
}