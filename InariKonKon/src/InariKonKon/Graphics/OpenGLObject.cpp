#include "InariKonKon/Graphics/OpenGLObject.hpp"

#include <utility>
#include <cassert>

ikk::priv::OpenGLObject::OpenGLObject(const std::uint32_t id) noexcept : m_id(id)
{
}

ikk::priv::OpenGLObject::OpenGLObject(const OpenGLObject& other) noexcept : m_id(std::exchange(other.m_id, 0))
{
}

ikk::priv::OpenGLObject::OpenGLObject(OpenGLObject&& other) noexcept : m_id(std::exchange(other.m_id, 0))
{
}

ikk::priv::OpenGLObject& ikk::priv::OpenGLObject::operator=(const OpenGLObject& other) noexcept
{
    if (this != &other)
    {
        this->release();
        this->m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

ikk::priv::OpenGLObject& ikk::priv::OpenGLObject::operator=(OpenGLObject&& other) noexcept
{
    if (this != &other)
    {
        this->release();
        this->m_id = other.m_id;
        other.m_id = 0;
    }
    return *this;
}

const std::uint32_t& ikk::priv::OpenGLObject::getNativeHandle() const noexcept
{
	return this->m_id;
}