#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

namespace ikk
{
	namespace priv
	{
		ElementBufferObject::ElementBufferObject(const std::uint32_t usage) noexcept : m_usage(usage)
		{
		}

		ElementBufferObject::~ElementBufferObject() noexcept
		{
			this->release();
		}

		void ElementBufferObject::bind() const noexcept
		{
			gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->getNativeHandle());
		}

		void ElementBufferObject::unbind() const noexcept
		{
			gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void ElementBufferObject::release() const noexcept
		{
			if (this->m_copied == false)
				gl->DeleteBuffers(1, &this->getNativeHandle());
		}

		const std::uint32_t& ElementBufferObject::getType() const noexcept
		{
			return this->m_type;
		}
	}
}