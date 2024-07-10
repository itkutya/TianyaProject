#include "InariKonKon/Graphics/Buffers/UniformBuffer.hpp"

namespace ikk
{
	namespace priv
	{
		UniformBuffer::UniformBuffer(const std::uint32_t usage) noexcept : m_usage(usage)
		{
			gl->GenBuffers(1, this->m_id.get());
		}

		UniformBuffer::~UniformBuffer() noexcept
		{
			this->release();
		}

		void UniformBuffer::bind() const noexcept
		{
			gl->BindBuffer(GL_UNIFORM_BUFFER, this->getNativeHandle());
		}

		void UniformBuffer::unbind() const noexcept
		{
			gl->BindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		void UniformBuffer::release() const noexcept
		{
			if (this->canBeDeleted())
				gl->DeleteBuffers(1, &this->getNativeHandle());
		}
	}
}