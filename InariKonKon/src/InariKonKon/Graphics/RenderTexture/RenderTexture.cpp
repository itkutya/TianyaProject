#include "InariKonKon/Graphics/RenderTexture/RenderTexture.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::RenderTexture::RenderTexture(const Vector2<std::uint32_t> screenSize) noexcept : m_buffer(screenSize)
{
	this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices }, this->m_EBO, std::span{ this->m_indices });
}

const ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() const noexcept
{
	return this->m_buffer;
}

ikk::priv::FrameBuffer& ikk::RenderTexture::getFrameBuffer() noexcept
{
	return this->m_buffer;
}

void ikk::RenderTexture::draw(const Shader& shader, const Texture& texture) const noexcept
{
	shader.bind();
	texture.bind();
	this->m_VAO.bind();
	gl->DrawElements(Primitive::Triangles, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), 0);
}