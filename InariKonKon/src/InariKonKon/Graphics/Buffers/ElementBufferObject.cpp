#include "InariKonKon/Graphics/Buffers/ElementBufferObject.hpp"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::priv::ElementBufferObject::ElementBufferObject(const std::span<std::uint32_t> indices, const Drawable::Type type) noexcept
{
	gl->GenBuffers(1, &this->m_id);
	//gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(std::uint32_t), &indices[0], static_cast<GLenum>(type));
}

ikk::priv::ElementBufferObject::~ElementBufferObject() noexcept
{
	gl->DeleteBuffers(1, &this->m_id);
}

void ikk::priv::ElementBufferObject::bind() noexcept
{
	gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_id);
}

void ikk::priv::ElementBufferObject::unbind() noexcept
{
	gl->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}