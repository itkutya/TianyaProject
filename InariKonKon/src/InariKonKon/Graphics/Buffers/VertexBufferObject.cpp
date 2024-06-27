#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"

namespace ikk
{
	namespace priv
	{
		VertexBufferObject::VertexBufferObject(const std::uint32_t usage) noexcept : m_usage(usage)
		{
		}

		VertexBufferObject::~VertexBufferObject() noexcept
		{
			this->release();
		}

		void VertexBufferObject::bind() const noexcept
		{
			gl->BindBuffer(GL_ARRAY_BUFFER, this->m_id);
		}

		void VertexBufferObject::unbind() const noexcept
		{
			gl->BindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBufferObject::release() const noexcept
		{
			if (this->m_id)
				gl->DeleteBuffers(1, &this->m_id);
			this->m_id = 0;
		}
	}
}