#include "InariKonKon/Window/Context/Context.hpp"

#include "InariKonKon/Graphics/OpenGL/glad/gl.h"

namespace ikk
{
	namespace priv
	{
		void Context::activateContextForWindow(const Context::WindowID windowID) noexcept
		{
			if (windowID != 0 && this->m_context.find(windowID) == this->m_context.end())
				this->addContext(windowID);
			this->m_activeWindowID = windowID;
		}

		const GladGLContext* const Context::getActiveContext() const noexcept
		{
			if (this->m_activeWindowID == 0)
				return nullptr;
			return this->m_context.at(this->m_activeWindowID).get();
		}

		GladGLContext* const Context::getActiveContext() noexcept
		{
			if (this->m_activeWindowID == 0)
				return nullptr;
			return this->m_context.at(this->m_activeWindowID).get();
		}

		const Context::WindowID& Context::getActiveWindowContextID() const noexcept
		{
			return this->m_activeWindowID;
		}

		void Context::addContext(const Context::WindowID windowID) noexcept
		{
			this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
		}
	}
}