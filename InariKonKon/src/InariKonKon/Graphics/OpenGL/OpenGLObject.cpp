#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"

namespace ikk
{
	namespace priv
	{
		OpenGLObject::OpenGLObject(const OpenGLObject& other) noexcept : m_id(other.m_id), m_copied(false)
		{
			other.m_copied = true;
		}

		OpenGLObject::OpenGLObject(OpenGLObject&& other) noexcept : m_id(other.m_id)
		{
			other.m_id = 0;
		}

		OpenGLObject& OpenGLObject::operator=(const OpenGLObject& other) noexcept
		{
			if (this != &other)
			{
				this->release();
				this->m_id = other.m_id;
				other.m_copied = true;
			}
			return *this;
		}

		OpenGLObject& OpenGLObject::operator=(OpenGLObject&& other) noexcept
		{
			if (this != &other)
			{
				this->release();
				this->m_id = other.m_id;
				other.m_copied = true;
			}
			return *this;
		}

		const std::uint32_t& OpenGLObject::getNativeHandle() const noexcept
		{
			return this->m_id;
		}
	}
}