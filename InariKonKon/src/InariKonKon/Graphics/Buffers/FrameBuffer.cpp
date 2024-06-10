#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"

#include <print>

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::priv::FrameBuffer::FrameBuffer(const Vector2<std::uint32_t> screenSize) noexcept
{
	gl->GenFramebuffers(1, &this->m_id);
    this->bind();
    this->m_texture.create(screenSize);
    gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, screenSize.x, screenSize.y, 0, GL_RGB16F, GL_UNSIGNED_BYTE, NULL);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_texture.getNativeHandle(), 0);
    
    gl->GenRenderbuffers(1, &rbo);
    gl->BindRenderbuffer(GL_RENDERBUFFER, rbo);
    gl->RenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenSize.x, screenSize.y);
    gl->FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (gl->CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::print("Error Framebuffer is not complete!\n");
    this->unbind();
}

ikk::priv::FrameBuffer::~FrameBuffer() noexcept
{
	this->release();
}

void ikk::priv::FrameBuffer::bind() const noexcept
{
	gl->BindFramebuffer(GL_FRAMEBUFFER, this->m_id);
}

void ikk::priv::FrameBuffer::unbind() const noexcept
{
	gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ikk::priv::FrameBuffer::release() const noexcept
{
	if (this->m_id)
		gl->DeleteFramebuffers(1, &this->m_id);
	this->m_id = 0;
}

const ikk::Texture& ikk::priv::FrameBuffer::getTexture() const noexcept
{
    return this->m_texture;
}

ikk::Texture& ikk::priv::FrameBuffer::getTexture() noexcept
{
    return this->m_texture;
}