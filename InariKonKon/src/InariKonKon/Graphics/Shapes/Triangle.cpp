#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

#include "glad/gl.h"

#include "InariKonKon/Window/Context/Context.hpp"

#include "InariKonKon/Window/Window.hpp"

ikk::Triangle::Triangle() noexcept : VBO(m_vertices)
{
	this->setup();
}

void ikk::Triangle::draw(const Window& target) noexcept
{
	shader.bind();
	this->VAO.bind();
	priv::gl()->DrawArrays(GL_TRIANGLES, 0, 3);
}

void ikk::Triangle::setup()
{
	this->VBO.bind();
	priv::gl()->BufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * VBO.vertices.size(), VBO.vertices.data(), GL_STATIC_DRAW);

	this->VAO.bind();
	priv::gl()->EnableVertexAttribArray(0);
	priv::gl()->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	priv::gl()->EnableVertexAttribArray(1);
	priv::gl()->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	priv::gl()->EnableVertexAttribArray(2);
	priv::gl()->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));

}