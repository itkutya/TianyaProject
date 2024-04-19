#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::VertexBufferObject::VertexBufferObject(const std::span<Vertex> vertices, const DrawType type) noexcept : vertices(vertices), type(type)
{
	priv::gl()->GenBuffers(1, &this->m_id);
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