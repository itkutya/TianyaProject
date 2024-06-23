module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module FrameBuffer;

import <print>;

import OpenGLObject;
import Context;
import Texture;
import Vector2;

export namespace ikk
{
	class FrameBuffer final : public OpenGLObject
	{
	public:
		FrameBuffer(const vec2u screenSize) noexcept;
		~FrameBuffer() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		//TODO:
		//void resize(const Vector2<std::uint32_t> size) noexcept;

		const Texture& getTexture() const noexcept;
		Texture& getTexture() noexcept;
	private:
		Texture m_texture;
		unsigned int rbo;
	};

	FrameBuffer::FrameBuffer(const vec2u screenSize) noexcept
	{
		gl->GenFramebuffers(1, &this->m_id);
		this->bind();

		this->m_texture.create(screenSize);
		this->m_texture.bind();
		gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, screenSize.x, screenSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		gl->FramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->m_texture.getNativeHandle(), 0);

		gl->GenRenderbuffers(1, &rbo);
		gl->BindRenderbuffer(GL_RENDERBUFFER, rbo);
		gl->RenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenSize.x, screenSize.y);
		gl->FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

		if (gl->CheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::print("Error Framebuffer is not complete!\nFrame buffer status {}.\n", gl->CheckFramebufferStatus(GL_FRAMEBUFFER));
		this->unbind();
	}

	FrameBuffer::~FrameBuffer() noexcept
	{
		this->release();
	}

	void FrameBuffer::bind() const noexcept
	{
		gl->BindFramebuffer(GL_FRAMEBUFFER, this->m_id);
	}

	void FrameBuffer::unbind() const noexcept
	{
		gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteFramebuffers(1, &this->m_id);
		this->m_id = 0;
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