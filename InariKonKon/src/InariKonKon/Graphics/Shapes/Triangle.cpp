#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

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
	this->m_VAO.setupVertexAttributes();
}