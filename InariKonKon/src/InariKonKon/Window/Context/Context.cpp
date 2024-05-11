#include "InariKonKon/Window/Context/Context.hpp"

#include <cassert>

void ikk::priv::Context::addContext(const std::uint32_t windowID) noexcept
{
	if (const auto search = this->m_context.find(windowID); search == this->m_context.end())
		this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
}

void ikk::priv::Context::activateContextForWindow(const std::uint32_t windowID) noexcept
{
	this->m_activeWindowID = windowID;
	this->m_activeContext = (windowID != 0) ? this->m_context.at(windowID) : nullptr;
}

const std::shared_ptr<GladGLContext>& ikk::priv::Context::getActiveContext() const noexcept
{
	return this->m_activeContext;
}

std::shared_ptr<GladGLContext>& ikk::priv::Context::getActiveContext() noexcept
{
	return this->m_activeContext;
}

const std::uint32_t& ikk::priv::Context::getWindowIDForTheActiveContext() const noexcept
{
	return this->m_activeWindowID;
}