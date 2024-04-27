#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::FrameBuffer::FrameBuffer() noexcept
{
	gl->GenFramebuffers(1, &this->m_id);
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