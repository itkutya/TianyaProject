#include "InariKonKon/Graphics/Shapes/Quad.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::Quad::Quad() noexcept
{
	this->VAO.bind();

	this->VBO.bind();
	gl->BufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->m_vertices.size(), &this->m_vertices[0], GL_STATIC_DRAW);

	this->EBO.bind();
	gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(std::uint32_t) * this->m_indices.size(), &this->m_indices[0], GL_STATIC_DRAW);

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	gl->EnableVertexAttribArray(2);
	gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

void ikk::Quad::draw(const Window& target, const RenderState& state) noexcept
{
	target.setActive();
	if (state.shader)
	{
		state.shader->bind();
		this->VAO.bind();
		gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), GL_UNSIGNED_INT, 0);
	}
	else
	{
		Shader defaultShader;
		defaultShader.bind();
		this->VAO.bind();
		gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), GL_UNSIGNED_INT, 0);
	}
}