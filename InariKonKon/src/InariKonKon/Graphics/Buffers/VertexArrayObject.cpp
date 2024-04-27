#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::VertexArrayObject::VertexArrayObject() noexcept
{
	gl->GenVertexArrays(1, &this->m_id);
}

ikk::priv::VertexArrayObject::~VertexArrayObject() noexcept
{
	this->release();
}

void ikk::priv::VertexArrayObject::bind() noexcept
{
	gl->BindVertexArray(this->m_id);
}

void ikk::priv::VertexArrayObject::unbind() noexcept
{
	gl->BindVertexArray(0);
}

void ikk::priv::VertexArrayObject::release() noexcept
{
	if (this->m_id)
		gl->DeleteVertexArrays(1, &this->m_id);
	this->m_id = 0;
}