#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

#include "InariKonKon/Utility/Math/Matrix.hpp"

ikk::Triangle::Triangle() noexcept
{
	this->VAO.bind();

	this->VBO.bind();
	gl->BufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->m_vertices.size(), &this->m_vertices[0], GL_STATIC_DRAW);

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	gl->EnableVertexAttribArray(2);
	gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

void ikk::Triangle::draw(const Window& target, const RenderState& state) const noexcept
{
	target.setActive();
	state.shader->bind();
	this->VAO.bind();
	gl->DrawArrays(GL_TRIANGLES, 0, 3);
}