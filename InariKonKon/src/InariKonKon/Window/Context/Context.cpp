#include "InariKonKon/Window/Context/Context.h"

const GladGLContext& ikk::priv::Context::getContext() const noexcept
{
	return this->m_context;
}

GladGLContext& ikk::priv::Context::getContext() noexcept
{
	return this->m_context;
}