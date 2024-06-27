#include "InariKonKon/Window/Context/Context.hpp"

//#include "InariKonKon/Graphics/external/glad/gl.h"

namespace ikk
{
	namespace priv
	{
		void Context::activateContextForWindow(const std::uint32_t windowID) noexcept
		{
			if (this->m_context.find(windowID) == this->m_context.end())
				this->addContext(windowID);
			this->m_activeWindowID = windowID;
		}

		const GladGLContext* const Context::getActiveContext() const noexcept
		{
			return this->m_context.at(this->m_activeWindowID).get();
		}

		GladGLContext* const Context::getActiveContext() noexcept
		{
			return this->m_context.at(this->m_activeWindowID).get();
		}

		const std::uint32_t& Context::getWindowIDForTheActiveWindowContext() const noexcept
		{
			return this->m_activeWindowID;
		}

		void Context::addContext(const std::uint32_t windowID) noexcept
		{
			//this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
		}
	}
}