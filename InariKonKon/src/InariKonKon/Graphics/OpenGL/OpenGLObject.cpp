#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"

#include <utility>

namespace ikk
{
	namespace priv
	{
		OpenGLObject::OpenGLObject(const OpenGLObject& other) noexcept : m_id(std::exchange(other.m_id, 0))
		{
		}

		OpenGLObject::OpenGLObject(OpenGLObject&& other) noexcept : m_id(std::exchange(other.m_id, 0))
		{
		}

		OpenGLObject& OpenGLObject::operator=(const OpenGLObject& other) noexcept
		{
			if (this != &other)
			{
				this->release();
				this->m_id = other.m_id;
				other.m_id = 0;
			}
			return *this;
		}

		OpenGLObject& OpenGLObject::operator=(OpenGLObject&& other) noexcept
		{
			if (this != &other)
			{
				this->release();
				this->m_id = other.m_id;
				other.m_id = 0;
			}
			return *this;
		}

		const std::uint32_t& OpenGLObject::getNativeHandle() const noexcept
		{
			return this->m_id;
		}
	}
}