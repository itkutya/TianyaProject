#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::priv::ElementBufferObject::ElementBufferObject(const Usage usage) noexcept : m_usage(usage)
{
}

ikk::priv::ElementBufferObject::~ElementBufferObject() noexcept
{
	this->release();
}

void ikk::priv::ElementBufferObject::bind() const noexcept
{
	gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
}

void ikk::priv::ElementBufferObject::unbind() const noexcept
{
	gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ikk::priv::ElementBufferObject::release() const noexcept
{
	if (this->m_id)
		gl->DeleteBuffers(1, &this->m_id);
	this->m_id = 0;
}

const ikk::GLType& ikk::priv::ElementBufferObject::getType() const noexcept
{
	return this->m_type;
}

void ikk::priv::ElementBufferObject::BufferDataImpl(const std::size_t size, const void* data) const noexcept
{
	if (this->m_id == 0)
		gl->GenBuffers(1, &this->m_id);
	this->bind();
	gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, this->m_usage);
}