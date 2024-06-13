module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module UniformBuffer;

import <span>;

export import OpenGLObject;
export import DrawEnums;

export namespace ikk
{
	class UniformBuffer final : public OpenGLObject
	{
	public:
		UniformBuffer(const Usage usage = Usage::Static) noexcept;
		~UniformBuffer() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		template<class T, std::size_t N>
		void BufferData(const std::span<T, N> data, const std::uint32_t binding = 0) const noexcept;
	private:
		Usage m_usage;

		void BufferDataImpl(const std::size_t size, const void* data, const std::uint32_t binding) const noexcept;
	};

	template<class T, std::size_t N>
	void UniformBuffer::BufferData(const std::span<T, N> data, const std::uint32_t binding) const noexcept
	{
		this->BufferDataImpl(sizeof(T) * data.size(), &data[0], binding);
	}


	UniformBuffer::UniformBuffer(const Usage usage) noexcept : m_usage(usage)
	{
	}

	UniformBuffer::~UniformBuffer() noexcept
	{
		this->release();
	}

	void UniformBuffer::bind() const noexcept
	{
		gl->BindBuffer(GL_UNIFORM_BUFFER, this->m_id);
	}

	void UniformBuffer::unbind() const noexcept
	{
		gl->BindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteBuffers(1, &this->m_id);
		this->m_id = 0;
	}

	void UniformBuffer::BufferDataImpl(const std::size_t size, const void* data, const std::uint32_t binding) const noexcept
	{
		if (this->m_id == 0)
		{
			gl->GenBuffers(1, &this->m_id);
			gl->BindBufferBase(GL_UNIFORM_BUFFER, binding, this->m_id);
		}
		this->bind();
		gl->BufferData(GL_UNIFORM_BUFFER, size, data, this->m_usage);
		this->unbind();
	}
}