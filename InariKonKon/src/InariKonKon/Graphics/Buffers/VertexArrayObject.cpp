#include "InariKonKon/Graphics/Buffers/VertexArrayObject.hpp"

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"

ikk::priv::VertexArrayObject::VertexArrayObject() noexcept
{
	this->unbind();
	priv::gl()->GenVertexArrays(1, &this->m_id);
	this->bind();
	//TODO:
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	priv::gl()->EnableVertexAttribArray(0);
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