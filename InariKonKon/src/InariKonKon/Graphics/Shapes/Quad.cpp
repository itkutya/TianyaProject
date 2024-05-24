#include "InariKonKon/Graphics/Shapes/Quad.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::Quad::Quad(const Color c) noexcept
{
	for (Vertex& vertex : this->m_vertices)
		vertex.color = c;

	this->VAO.bind();

	this->VBO.bind();
	gl->BufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->m_vertices.size(), &this->m_vertices[0], GL_STATIC_DRAW);

	this->EBO.BufferData(std::span{ this->m_indices });

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	gl->EnableVertexAttribArray(2);
	gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

void ikk::Quad::draw(const Window& target, const RenderState& state) const noexcept
{
	target.setActive();
	state.shader->bind();
	if (state.texture)
	{
		gl->ActiveTexture(GL_TEXTURE0);
		gl->BindTexture(GL_TEXTURE_2D, state.texture);
	}
	this->VAO.bind();
	gl->DrawElements(Draw::Primitive::Triangles, static_cast<GLsizei>(this->m_indices.size()), this->EBO.getType(), 0);
}