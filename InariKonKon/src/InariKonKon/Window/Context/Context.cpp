#include "InariKonKon/Window/Context/Context.hpp"

#include <cassert>

#include "InariKonKon/Window/Window.hpp"

void ikk::priv::Context::addContext(const Window& window) noexcept
{
	if (auto search = this->m_context.find(window.getID()); search != this->m_context.end())
		assert(false && "Window with similiar name already exists!");
	else
		this->m_context.emplace(window.getID(), std::make_shared<GladGLContext>());
}

void ikk::priv::Context::activateContextForWindow(const Window* const window) noexcept
{
	if (window != nullptr)
	{
		this->m_activeWindowID = window->getID();
		this->m_activeContext = this->m_context.at(window->getID());
	}
	else
	{
		this->m_activeWindowID = 0;
		this->m_activeContext = nullptr;
	}
}

const GladGLContext* const ikk::priv::Context::getActiveContext() const noexcept
{
	return this->m_activeContext.get();
}

GladGLContext* const ikk::priv::Context::getActiveContext() noexcept
{
	return this->m_activeContext.get();
}

const std::uint32_t& ikk::priv::Context::getWindowIDForTheActiveContext() const noexcept
{
	return this->m_activeWindowID;
}