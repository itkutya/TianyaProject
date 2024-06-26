#include "InariKonKon/Graphics/Buffers/ElementBuffer.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

namespace ikk
{
	namespace priv
	{
		ElementBufferObject::ElementBufferObject(const Usage usage) noexcept : m_usage(usage)
		{
		}

		ElementBufferObject::~ElementBufferObject() noexcept
		{
			this->release();
		}

		void ElementBufferObject::bind() const noexcept
		{
			gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
		}

		void ElementBufferObject::unbind() const noexcept
		{
			gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void ElementBufferObject::release() const noexcept
		{
			if (this->m_id)
				gl->DeleteBuffers(1, &this->m_id);
			this->m_id = 0;
		}

		const ikk::GLType& ElementBufferObject::getType() const noexcept
		{
			return this->m_type;
		}
	}
}