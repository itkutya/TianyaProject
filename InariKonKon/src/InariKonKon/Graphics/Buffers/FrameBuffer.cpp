#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"

#include <print>

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::FrameBuffer::FrameBuffer() noexcept
{
	gl->GenFramebuffers(1, &this->m_id);
    this->bind();
    gl->GenTextures(1, &textureColorbuffer);
    gl->BindTexture(GL_TEXTURE_2D, textureColorbuffer);
    gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 500, 500, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    
    gl->GenRenderbuffers(1, &rbo);
    gl->BindRenderbuffer(GL_RENDERBUFFER, rbo);
    gl->RenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 500, 500);
    gl->FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if (gl->CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::print("Error Framebuffer is not complete!\n");
    this->unbind();
}

ikk::priv::FrameBuffer::~FrameBuffer() noexcept
{
	this->release();
}

void ikk::priv::FrameBuffer::bind() noexcept
{
	gl->BindFramebuffer(GL_FRAMEBUFFER, this->m_id);
}

void ikk::priv::FrameBuffer::unbind() noexcept
{
	gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ikk::priv::FrameBuffer::release() noexcept
{
	if (this->m_id)
		gl->DeleteFramebuffers(1, &this->m_id);
	this->m_id = 0;
}