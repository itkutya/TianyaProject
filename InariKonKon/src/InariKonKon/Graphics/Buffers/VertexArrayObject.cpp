#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"

#include <cstddef>

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"

ikk::priv::VertexArrayObject::VertexArrayObject() noexcept
{
	priv::gl()->GenVertexArrays(1, &this->m_id);
}

ikk::priv::VertexArrayObject::~VertexArrayObject() noexcept
{
	priv::gl()->DeleteVertexArrays(1, &this->m_id);
}

void ikk::priv::VertexArrayObject::bind() noexcept
{
	priv::gl()->BindVertexArray(this->m_id);
}

void ikk::priv::VertexArrayObject::unbind() noexcept
{
	priv::gl()->BindVertexArray(0);
}