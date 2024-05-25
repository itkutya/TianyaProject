#include "InariKonKon/Window/Context/Context.hpp"

#include <cassert>

#include "glad/gl.h"

void ikk::priv::Context::addContext(const std::uint32_t windowID) noexcept
{
	if (this->m_context.find(windowID) == this->m_context.end())
		this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
}

void ikk::priv::Context::activateContextForWindow(const std::uint32_t windowID) noexcept
{
	this->m_activeWindowID = windowID;
}

const std::shared_ptr<GladGLContext>& ikk::priv::Context::getActiveContext() const noexcept
{
	assert((this->m_context.find(this->m_activeWindowID) != this->m_context.end()) && "There is no openGL context set!");
	return this->m_context.at(this->m_activeWindowID);
}

std::shared_ptr<GladGLContext>& ikk::priv::Context::getActiveContext() noexcept
{
	assert((this->m_context.find(this->m_activeWindowID) != this->m_context.end()) && "There is no openGL context set!");
	return this->m_context.at(this->m_activeWindowID);
}

const std::uint32_t& ikk::priv::Context::getWindowIDForTheActiveContext() const noexcept
{
	return this->m_activeWindowID;
}