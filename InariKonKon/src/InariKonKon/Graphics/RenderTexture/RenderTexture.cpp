#include "InariKonKon/Graphics/RenderTexture/RenderTexture.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::RenderTexture::RenderTexture(const Vector2<std::uint32_t> screenSize) noexcept : m_buffer(screenSize)
{
}

const ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() const noexcept
{
	return this->m_buffer;
}

ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() noexcept
{
	return this->m_buffer;
}

void ikk::RenderTexture::display(const Window& target, const RenderState& state) const noexcept
{
	this->m_screen.draw(target, state);
}