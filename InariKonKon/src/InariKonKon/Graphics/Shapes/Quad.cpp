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

	if (state.camera != nullptr)
	{
		mat4x4 model(1.f);
		state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix());
		state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
		state.shader->setMatrix4x4("model", model);
	}

	this->m_VAO.bind();
	gl->DrawElements(Draw::Primitive::Triangles, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
}

void ikk::Quad::setup() noexcept
{
	this->m_VAO.bind();
	this->m_VBO.BufferData(std::span{ this->m_vertices });
	this->m_EBO.BufferData(std::span{ this->m_indices });
	this->m_VAO.setupVertexAttributes();
}