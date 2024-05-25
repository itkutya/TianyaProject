#include "InariKonKon/Graphics/Shapes/Quad.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::Quad::Quad(const Color c) noexcept
{
	for (Vertex& vertex : this->m_vertices)
		vertex.color = c;

	this->setup();
}

void ikk::Quad::draw(const Window& target, const RenderState& state) const noexcept
{
	target.setActive();
	state.shader->bind();
	if (state.texture)
		state.texture->bind();
	this->m_VAO.bind();
	gl->DrawElements(Draw::Primitive::Triangles, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
}

void ikk::Quad::setup() noexcept
{
	this->m_VAO.bind();

	this->m_VBO.bind();
	gl->BufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->m_vertices.size(), &this->m_vertices[0], GL_STATIC_DRAW);

	this->m_EBO.BufferData(std::span{ this->m_indices });

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	gl->EnableVertexAttribArray(2);
	gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}