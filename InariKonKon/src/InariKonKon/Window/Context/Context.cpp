#include "InariKonKon/Window/Context/Context.hpp"

#include "glad/gl.h"

namespace ikk
{
	namespace priv
	{
		void Context::addContext(const std::uint32_t windowID) noexcept
		{
			if (this->m_context.find(windowID) == this->m_context.end())
				this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
		}

		void Context::activateContextForWindow(const std::uint32_t windowID) noexcept
		{
			if (this->m_context.find(windowID) == this->m_context.end())
				this->addContext(windowID);
			this->m_activeWindowID = windowID;
		}

		const GladGLContext* const Context::getActiveContext() const noexcept
		{
			if (this->m_context.find(this->m_activeWindowID) == this->m_context.end())
				return nullptr;
			return this->m_context.at(this->m_activeWindowID).get();
		}

		GladGLContext* const Context::getActiveContext() noexcept
		{
			if (this->m_context.find(this->m_activeWindowID) == this->m_context.end())
				return nullptr;
			return this->m_context.at(this->m_activeWindowID).get();
		}

		const std::uint32_t& Context::getWindowIDForTheActiveContext() const noexcept
		{
			return this->m_activeWindowID;
		}
	}
}