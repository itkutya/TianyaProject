#include "InariKonKon/Graphics/Texture/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "InariKonKon/Window/Context/Context.hpp"

ikk::Texture::Texture(const std::filesystem::path path, const std::uint32_t slot) noexcept : m_slot(slot)
{
    gl->ActiveTexture(GL_TEXTURE0 + this->m_slot);
    gl->GenTextures(1, &this->m_id);
    gl->BindTexture(GL_TEXTURE_2D, this->m_id);

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

    gl->BindTexture(GL_TEXTURE_2D, 0);
}

ikk::Texture::~Texture() noexcept
{
    this->release();
    stbi_image_free(this->m_data);
}

void ikk::Texture::bind() const noexcept
{
}

void ikk::Texture::unbind() const noexcept
{
}

void ikk::Texture::release() const noexcept
{
    if (this->m_id)
        gl->DeleteTextures(1, &this->m_id);
    this->m_id = 0;
}