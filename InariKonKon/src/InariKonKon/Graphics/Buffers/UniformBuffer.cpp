#include "InariKonKon/Graphics/Buffers/UniformBuffer.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::priv::UniformBuffer::UniformBuffer(const std::uint32_t binding, const Usage usage) noexcept : m_binding(binding), m_usage(usage)
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

const std::uint32_t ikk::priv::UniformBuffer::getBindingSlot() const noexcept
{
	return this->m_binding;
}

void ikk::priv::UniformBuffer::BufferDataImpl(const std::size_t size, const void* data) const noexcept
{
	if (this->m_id == 0)
		gl->GenBuffers(1, &this->m_id);
	this->bind();
	gl->BufferData(GL_UNIFORM_BUFFER, size, data, this->m_usage);
	gl->BindBufferBase(GL_UNIFORM_BUFFER, this->m_binding, this->m_id);
	this->unbind();
}