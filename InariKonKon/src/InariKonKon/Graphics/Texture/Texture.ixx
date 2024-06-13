module;

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "stb_image.h"

export module Texture;

import <filesystem>;

export import OpenGLObject;
export import Vector2;

import Typedefs;

export namespace ikk
{
	class Texture : public OpenGLObject
	{
	public:
		Texture(const std::uint32_t slot = 0) noexcept;
		Texture(const std::filesystem::path path, const std::uint32_t slot = 0) noexcept;
		~Texture() noexcept;

		void bind() const noexcept override;
		void unbind() const noexcept override;
		void release() const noexcept override;

		template<Number T>
		void create(const Vector2<T> size) noexcept;

		const bool loadFromDisc(const std::filesystem::path path) noexcept;
		const bool loadFromMemory(const std::uint8_t* const data) noexcept;

		const std::uint32_t getTextureSlot() const noexcept;
	private:
		std::uint32_t m_slot;
		int m_width = 0;
		int m_height = 0;
		int m_channels = 0;
		std::uint8_t* m_data = nullptr;

		void createImpl() noexcept;
	};

	Texture::Texture(const std::uint32_t slot) noexcept : m_slot(slot)
	{
	}

	Texture::Texture(const std::filesystem::path path, const std::uint32_t slot) noexcept
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

	Texture::~Texture() noexcept
	{
		this->release();
		stbi_image_free(this->m_data);
	}

	void Texture::bind() const noexcept
	{
		gl->ActiveTexture(GL_TEXTURE0 + this->m_slot);
		gl->BindTexture(GL_TEXTURE_2D, this->m_id);
	}

	void Texture::unbind() const noexcept
	{
		gl->ActiveTexture(GL_TEXTURE0);
		gl->BindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::release() const noexcept
	{
		if (this->m_id)
			gl->DeleteTextures(1, &this->m_id);
		this->m_id = 0;
	}

	template<Number T>
	void Texture::create(const Vector2<T> size) noexcept
	{
		this->m_width = static_cast<int>(size.x);
		this->m_height = static_cast<int>(size.y);
		this->createImpl();
	}

	const bool Texture::loadFromDisc(const std::filesystem::path path) noexcept
	{
		return false;
	}

	const bool ikk::Texture::loadFromMemory(const std::uint8_t* const data) noexcept
	{
		return false;
	}
	const std::uint32_t Texture::getTextureSlot() const noexcept
	{
		return this->m_slot;
	}

	void Texture::createImpl() noexcept
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
}