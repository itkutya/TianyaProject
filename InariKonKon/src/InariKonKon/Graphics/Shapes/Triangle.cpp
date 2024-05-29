#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::Triangle::Triangle() noexcept
{
	this->setup();
}

void ikk::Triangle::draw(const Window& target, const RenderState<Draw::Dimension::_2D, Projection::Orhto>& state) const noexcept
{
	gl->Enable(GL_DEPTH_TEST);

	state.shader->bind();

	if (state.texture)
		state.texture->bind();

	if (state.camera != nullptr)
	{
		mat4x4 model(1.f);
		state.shader->setMatrix4x4("model", model);
		state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
		//state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(target.getAspectRatio()));
	}

	this->m_VAO.bind();
	gl->DrawArrays(GL_TRIANGLES, 0, 3);
}

void ikk::Triangle::draw(const Window& target, const RenderState<Draw::Dimension::_2D, Projection::Perspective>& state) const noexcept
{
	gl->Enable(GL_DEPTH_TEST);

	state.shader->bind();

	if (state.texture)
		state.texture->bind();

	if (state.camera != nullptr)
	{
		mat4x4 model(1.f);
		state.shader->setMatrix4x4("model", model);
		state.shader->setMatrix4x4("view", state.camera->getViewMatrix());
		state.shader->setMatrix4x4("projection", state.camera->getProjectionMatrix(target.getAspectRatio()));
	}

	this->m_VAO.bind();
	gl->DrawArrays(GL_TRIANGLES, 0, 3);
}

void ikk::Triangle::setup() noexcept
{
	this->m_VAO.bind();
	this->m_VBO.BufferData(std::span{ this->m_vertices });
	this->m_VAO.setupVertexAttributes();
}