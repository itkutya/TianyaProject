#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

#include "InariKonKon/Utility/Math/Matrix.hpp"

ikk::Triangle::Triangle() noexcept
{
	this->setup();
}

void ikk::Triangle::draw(const Window& target, const RenderState& state) const noexcept
{
	target.setActive();
	state.shader->bind();
	if (state.texture)
		state.texture->bind();
	this->m_VAO.bind();
	gl->DrawArrays(GL_TRIANGLES, 0, 3);
}

void ikk::Triangle::setup() noexcept
{
	this->m_VAO.bind();

	this->m_VBO.BufferData(std::span{ this->m_vertices });

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

	gl->EnableVertexAttribArray(2);
	gl->VertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}