#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::VertexBufferObject::VertexBufferObject() noexcept
{
	gl->GenBuffers(1, &this->m_id);
}

ikk::priv::VertexBufferObject::~VertexBufferObject() noexcept
{
	this->release();
}

void ikk::priv::VertexBufferObject::bind() const noexcept
{
	gl->BindBuffer(GL_ARRAY_BUFFER, this->m_id);
}

void ikk::priv::VertexBufferObject::unbind() const noexcept
{
	gl->BindBuffer(GL_ARRAY_BUFFER, 0);
}

void ikk::priv::VertexBufferObject::release() const noexcept
{
	if (this->m_id)
		gl->DeleteBuffers(1, &this->m_id);
	this->m_id = 0;
}