#pragma once

#include <array>

#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

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

		virtual const Quad2D& getScreenQuad() const noexcept;
	private:
		Quad2D m_screen;
		priv::FrameBuffer m_buffer;
	};
}