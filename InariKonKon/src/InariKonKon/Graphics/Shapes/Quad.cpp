#include "InariKonKon/Graphics/Shapes/Quad.h"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::Quad::Quad() noexcept
{
	this->VAO.bind();

	this->EBO.bind();
	gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(this->m_indices), this->m_indices, GL_STATIC_DRAW);
	this->VBO.bind();
	gl->BufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 3, &this->m_vertices[0], GL_STATIC_DRAW);

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	gl->EnableVertexAttribArray(2);
	gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

void ikk::Quad::draw(const Window& target) noexcept
{
	target.setActive();
	this->VAO.bind();
	gl->DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}