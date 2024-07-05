#include "InariKonKon/Graphics/Texture/Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace ikk
{
	Texture::Texture(const Texture::Settings settings, const std::uint32_t slot) noexcept : m_slot(slot), m_settings(settings)
	{
	}

	Texture::Texture(const vec2u size, const Texture::Settings settings, const std::uint32_t slot) noexcept : m_slot(slot), m_settings(settings)
	{
		this->create(size);
	}

	Texture::Texture(const std::filesystem::path path, const ikk::Texture::Settings settings, const std::uint32_t slot) noexcept : m_slot(slot), m_settings(settings)
	{
		gl->GenTextures(1, &this->m_id);
		this->bind();
		if (this->loadFromDisc(path))
			this->setUpSettings();
		this->unbind();
	}

	Texture::~Texture() noexcept
	{
		this->release();
	}

	void Texture::bind() const noexcept
	{
		gl->BindTexture(GL_TEXTURE_2D, this->m_id);
		gl->ActiveTexture(GL_TEXTURE0 + this->m_slot);
	}

	void Texture::unbind() const noexcept
	{
		gl->BindTexture(GL_TEXTURE_2D, 0);
		gl->ActiveTexture(GL_TEXTURE0);
	}

	void Texture::release() const noexcept
	{
		if (this->m_id)
		{
			gl->DeleteTextures(1, &this->m_id);
			this->m_id = 0;

			if (this->m_data)
				stbi_image_free(this->m_data);
		}
	}

	const bool Texture::loadFromDisc(const std::filesystem::path path) noexcept
	{
		stbi_set_flip_vertically_on_load(true);
		int width = 0, height = 0, channels = 0;
		this->m_data = stbi_load(path.generic_string().c_str(), &width, &height, &channels, 0);
		if (this->m_data)
		{
			this->m_width = static_cast<std::uint32_t>(width);
			this->m_height = static_cast<std::uint32_t>(height);
			this->m_channels = static_cast<std::uint32_t>(channels);

			gl->TexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->m_width, this->m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, this->m_data);
			return true;
		}
		else
		{
			this->release();
			return false;
		}
	}

	//TODO:
	const bool ikk::Texture::loadFromMemory(const std::uint8_t* const data) noexcept
	{
		return false;
	}

	const std::uint32_t& Texture::getTextureSlot() const noexcept
	{
		return this->m_slot;
	}

	const vec2u Texture::getSize() const noexcept
	{
		return vec2u{ this->m_width, this->m_height };
	}

	void Texture::create(const vec2u size) noexcept
	{
		this->release();

		this->m_width = size.x;
		this->m_height = size.y;
		this->m_channels = 0;
		this->m_data = nullptr;

		gl->GenTextures(1, &this->m_id);
		this->bind();
		gl->TexImage2D(GL_TEXTURE_2D, 0, static_cast<decltype(std::to_underlying(this->m_settings.type))>(this->m_settings.type), 
			this->m_width, this->m_height, 0, static_cast<decltype(std::to_underlying(this->m_settings.type))>(this->m_settings.type), GL_UNSIGNED_BYTE, this->m_data);

		this->setUpSettings();
		this->unbind();
	}

	void Texture::setUpSettings() const noexcept
	{
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<decltype(std::to_underlying(this->m_settings.wrapping))>(this->m_settings.wrapping));
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<decltype(std::to_underlying(this->m_settings.wrapping))>(this->m_settings.wrapping));
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<decltype(std::to_underlying(this->m_settings.minFilter))>(this->m_settings.minFilter));
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<decltype(std::to_underlying(this->m_settings.magFilter))>(this->m_settings.magFilter));
		if (this->m_settings.generateMipMap)
			gl->GenerateMipmap(GL_TEXTURE_2D);
	}
}