#include "InariKonKon/Window/Context/Context.h"

#include <cassert>

#include "glad/gl.h"

#include "InariKonKon/Window/Window.hpp"

void ikk::priv::Context::addContext(const Window* const window) noexcept
{
	if (auto search = this->m_context.find(window->getTitle()); search != this->m_context.end())
		assert(false && "Window with similiar name already exists!");
	else
		this->m_context.emplace(window->getTitle(), std::make_shared<GladGLContext>());
}

void ikk::priv::Context::activateContextForWindow(const Window* const window) noexcept
{
	this->m_activeContext = ((window != nullptr) ? this->m_context.at(window->getTitle()) : nullptr);
}

const GladGLContext* const ikk::priv::Context::getActiveContext() const noexcept
{
	return this->m_activeContext.get();
}

GladGLContext* const ikk::priv::Context::getActiveContext() noexcept
{
	return this->m_activeContext.get();
}