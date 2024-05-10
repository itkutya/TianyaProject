#pragma once

#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"

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

		virtual void onResize(const Vector2<std::uint32_t> screenSize) noexcept final;

		[[nodiscard]] virtual const	priv::FrameBuffer& getFrameBuffer() const	noexcept final;
		[[nodiscard]] virtual		priv::FrameBuffer& getFrameBuffer()			noexcept final;

		//[[nodiscard]] virtual const	Vector2<std::uint32_t> getFrameBufferSize() const	noexcept final;
		//[[nodiscard]] virtual		Vector2<std::uint32_t> getFrameBufferSize()			noexcept final;
		virtual void display(Window& window, const RenderState& state) noexcept final;
	protected:
	private:
		Quad m_screen;
		priv::FrameBuffer m_buffer;
	};
}