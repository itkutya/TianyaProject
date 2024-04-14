#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::ElementBufferObject::ElementBufferObject(const std::span<std::uint32_t> indices, const DrawType type) noexcept
{
	this->unbind();
	priv::gl()->GenBuffers(1, &this->m_id);
	this->bind();
	//TODO:
	//priv::gl()->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), static_cast<const void*>(&indices), static_cast<GLenum>(type));
}

ikk::priv::ElementBufferObject::~ElementBufferObject() noexcept
{
	priv::gl()->DeleteBuffers(1, &this->m_id);
}

void ikk::priv::ElementBufferObject::bind() noexcept
{
	priv::gl()->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
}

void ikk::priv::ElementBufferObject::unbind() noexcept
{
	priv::gl()->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}