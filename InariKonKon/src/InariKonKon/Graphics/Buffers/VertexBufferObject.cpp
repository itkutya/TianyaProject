#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::VertexBufferObject::VertexBufferObject(const std::span<Vertex> vertices, const DrawType type) noexcept
{
	this->unbind();
	priv::gl()->GenBuffers(1, &this->m_id);
	this->bind();
	//TODO:
	//priv::gl()->BufferData(GL_ARRAY_BUFFER, sizeof(vertices), static_cast<const void*>(&vertices), static_cast<GLenum>(type));
}

ikk::priv::VertexBufferObject::~VertexBufferObject() noexcept
{
	priv::gl()->DeleteBuffers(1, &this->m_id);
}

void ikk::priv::VertexBufferObject::bind() noexcept
{
	priv::gl()->BindBuffer(GL_ARRAY_BUFFER, this->m_id);
}

void ikk::priv::VertexBufferObject::unbind() noexcept
{
	priv::gl()->BindBuffer(GL_ARRAY_BUFFER, 0);
}