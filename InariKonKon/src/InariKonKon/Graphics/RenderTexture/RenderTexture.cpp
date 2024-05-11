#include "InariKonKon/Graphics/RenderTexture/RenderTexture.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::RenderTexture::RenderTexture(const Vector2<std::uint32_t> screenSize) noexcept : m_buffer(screenSize), m_screen(ikk::Color::Transparent)
{
}

void ikk::RenderTexture::onResize(const Vector2<std::uint32_t> screenSize) noexcept
{
	//TODO:
}

const ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() const noexcept
{
	return this->m_buffer;
}

ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() noexcept
{
	return this->m_buffer;
}

void ikk::RenderTexture::display(const Window& window, const RenderState& state) const noexcept
{
	window.draw(this->m_screen, state);
}