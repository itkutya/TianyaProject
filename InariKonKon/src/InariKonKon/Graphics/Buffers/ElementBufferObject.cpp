#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::ElementBufferObject::ElementBufferObject(const Draw::Usage usage) noexcept : m_usage(usage)
{
	gl->GenBuffers(1, &this->m_id);
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

const ikk::priv::GLType& ikk::priv::ElementBufferObject::getType() const noexcept
{
	return this->m_type;
}

void ikk::priv::ElementBufferObject::BufferDataImpl(const std::size_t size, const void* data) const noexcept
{
	this->bind();
	gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, static_cast<GLenum>(this->m_usage));
}