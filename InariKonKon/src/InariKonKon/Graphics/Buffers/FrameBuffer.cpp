#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"

#include <print>

#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"

namespace ikk
{
	namespace priv
	{
		FrameBuffer::FrameBuffer(const vec2u screenSize) noexcept
			: m_texture(Texture::Settings{ .type = Texture::Type::RGBA, .wrapping = Texture::Wrapping::ClampToBorder, .minFilter = Texture::MinFilter::Linear, .magFilter = Texture::MagFilter::Linear })
		{
			this->resize(screenSize);
		}

		FrameBuffer::~FrameBuffer() noexcept
		{
			this->release();
		}

		void FrameBuffer::bind() const noexcept
		{
			gl->BindFramebuffer(GL_FRAMEBUFFER, this->getNativeHandle());
		}

		void FrameBuffer::unbind() const noexcept
		{
			gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBuffer::release() const noexcept
		{
			this->m_texture.release();

			gl->DeleteRenderbuffers(1, &rbo);

			if (this->canBeDeleted())
				gl->DeleteFramebuffers(1, &this->getNativeHandle());
		}

		void FrameBuffer::resize(const vec2u newSize) noexcept
		{
			this->release();

			gl->GenFramebuffers(1, this->m_id.get());
			this->bind();

			this->m_texture.create(newSize);
			this->m_texture.bind();
			gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_texture.getNativeHandle(), 0);

			gl->GenRenderbuffers(1, &rbo);
			gl->BindRenderbuffer(GL_RENDERBUFFER, rbo);
			gl->RenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, newSize.x, newSize.y);
			gl->FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

			if (gl->CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::print("Error Framebuffer is not complete!\nFrame buffer status {}.\n", gl->CheckFramebufferStatus(GL_FRAMEBUFFER));
			this->unbind();
		}

		const Texture& FrameBuffer::getTexture() const noexcept
		{
			return this->m_texture;
		}

		Texture& FrameBuffer::getTexture() noexcept
		{
			return this->m_texture;
		}
	}
}