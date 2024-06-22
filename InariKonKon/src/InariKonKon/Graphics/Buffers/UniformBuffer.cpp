#include "InariKonKon/Graphics/Buffers/UniformBuffer.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::priv::UniformBuffer::UniformBuffer(const Usage usage) noexcept : m_usage(usage)
{
}

ikk::priv::UniformBuffer::~UniformBuffer() noexcept
{
	this->release();
}

void ikk::priv::UniformBuffer::bind() const noexcept
{
	gl->BindBuffer(GL_UNIFORM_BUFFER, this->m_id);
}

void ikk::priv::UniformBuffer::unbind() const noexcept
{
	gl->BindBuffer(GL_UNIFORM_BUFFER, 0);
}

void ikk::priv::UniformBuffer::release() const noexcept
{
	if (this->m_id)
		gl->DeleteBuffers(1, &this->m_id);
	this->m_id = 0;
}

void ikk::priv::UniformBuffer::BufferDataImpl(const std::size_t size, const void* data, const std::uint32_t binding) const noexcept
{
	if (this->m_id == 0)
		gl->GenBuffers(1, &this->m_id);

	this->bind();
	gl->BindBufferBase(GL_UNIFORM_BUFFER, binding, this->m_id);
	gl->BufferData(GL_UNIFORM_BUFFER, size, data, this->m_usage);
	this->unbind();
}