#include "InariKonKon/Graphics/RenderTexture/RenderTexture.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::RenderTexture::RenderTexture(const Vector2<std::uint32_t> screenSize) noexcept : m_buffer(screenSize)
{
	this->VAO.bind();

	this->VBO.bind();
	gl->BufferData(GL_ARRAY_BUFFER, this->m_vertices.size() * sizeof(float), &this->m_vertices[0], GL_STATIC_DRAW);

	this->EBO.bind();
	gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, this->m_indices.size() * sizeof(std::uint32_t), &this->m_indices[0], GL_STATIC_DRAW);

	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

const ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() const noexcept
{
	return this->m_buffer;
}

ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() noexcept
{
	return this->m_buffer;
}

void ikk::RenderTexture::display(const Window& window, const RenderState& state) const noexcept
{
	window.setActive();
	state.shader->bind();
	if (state.texture)
		state.texture->bind();
	this->VAO.bind();
	gl->DrawElements(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), GL_UNSIGNED_INT, 0);
}