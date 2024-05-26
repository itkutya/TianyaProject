#include "InariKonKon/Graphics/Texture/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "InariKonKon/Graphics/OpenGL.hpp"

ikk::Texture::Texture(const std::uint32_t slot) noexcept : m_slot(slot)
{
}

ikk::Texture::Texture(const std::filesystem::path path, const std::uint32_t slot) noexcept : m_slot(slot)
{
    gl->GenTextures(1, &this->m_id);
    this->bind();

    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    this->m_data = stbi_load(path.string().c_str(), &this->m_width, &this->m_height, &this->m_channels, 0);
    if (this->m_data)
    {
        gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_data);
        gl->GenerateMipmap(GL_TEXTURE_2D);
    }
    else
        this->release();

    this->unbind();
}

ikk::Texture::~Texture() noexcept
{
    this->release();
    stbi_image_free(this->m_data);
}

void ikk::Texture::bind() const noexcept
{
    gl->ActiveTexture(GL_TEXTURE0 + this->m_slot);
    gl->BindTexture(GL_TEXTURE_2D, this->m_id);
}

void ikk::Texture::unbind() const noexcept
{
    gl->ActiveTexture(GL_TEXTURE0);
    gl->BindTexture(GL_TEXTURE_2D, 0);
}

void ikk::Texture::release() const noexcept
{
    if (this->m_id)
        gl->DeleteTextures(1, &this->m_id);
    this->m_id = 0;
}

const bool ikk::Texture::loadFromDisc(const std::filesystem::path path) noexcept
{
    return false;
}

const bool ikk::Texture::loadFromMemory(const std::uint8_t* const data) noexcept
{
    return false;
}

const std::uint32_t ikk::Texture::getTextureSlot() const noexcept
{
    return this->m_slot;
}

void ikk::Texture::createImpl() noexcept
{
    this->release();

    gl->GenTextures(1, &this->m_id);
    this->bind();

    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_data);
    gl->GenerateMipmap(GL_TEXTURE_2D);
}