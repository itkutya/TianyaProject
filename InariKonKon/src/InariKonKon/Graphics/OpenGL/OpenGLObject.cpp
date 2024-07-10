#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"

#include <utility>

namespace ikk
{
	namespace priv
	{
		const std::uint32_t& OpenGLObject::getNativeHandle() const noexcept
		{
			return *this->m_id;
		}
		const bool OpenGLObject::canBeDeleted() const noexcept
		{
			return this->m_id.use_count() == 1;
		}
	}
}