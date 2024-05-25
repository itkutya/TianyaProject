#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::priv::VertexBufferObject::VertexBufferObject(const Draw::Usage usage) noexcept : m_usage(usage)
{
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

void ikk::priv::VertexBufferObject::BufferDataImpl(const std::size_t size, const void* data) const noexcept
{
	if (this->m_id == 0)
		gl->GenBuffers(1, &this->m_id);
	this->bind();
	gl->BufferData(GL_ARRAY_BUFFER, size, data, this->m_usage);
}