#include "InariKonKon/Graphics/UI/Text/Font.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"

namespace ikk
{
	Font::Font(const std::filesystem::path path)
		: m_texture(Texture::Settings{ .type = Texture::Type::Red, .wrapping = Texture::Wrapping::ClampToEdge, .minFilter = Texture::MinFilter::Linear, .magFilter = Texture::MagFilter::Linear })
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			throw;

		FT_Face face;
		if (FT_New_Face(ft, path.generic_string().c_str(), 0, &face))
			throw;

		FT_Set_Pixel_Sizes(face, 0, 24);

		this->m_glyphs.clear();

		for (char8_t c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				throw;

			this->m_width += face->glyph->bitmap.width;
			this->m_height = std::max(this->m_height, face->glyph->bitmap.rows);
		}

		const std::uint32_t padding = 2u;
		this->m_texture.create(vec2u{ this->m_width + (padding * 2u) * 128u, this->m_height + (padding * 2u) });
		this->m_texture.bind();
		gl->PixelStorei(GL_UNPACK_ALIGNMENT, 1);

		int x = padding;
		for (char8_t c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				throw;

			gl->TexSubImage2D(
				GL_TEXTURE_2D,
				0,
				x,
				padding,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			Glyph glyph;

			glyph.width = face->glyph->bitmap.width;
			glyph.height = face->glyph->bitmap.rows;
			glyph.bearing = { (float)face->glyph->bitmap_left, (float)face->glyph->bitmap_top };
			glyph.advance = { static_cast<std::uint32_t>(face->glyph->advance.x >> 6), static_cast<std::uint32_t>(face->glyph->advance.y >> 6) };

			//Freetype uses different types of coord system...
			glyph.bounds.left = (float)x / (float)this->m_texture.getSize().x;
			glyph.bounds.top = static_cast<float>(padding + glyph.height) / static_cast<float>(this->m_texture.getSize().y);
			glyph.bounds.right = static_cast<float>(x + glyph.width) / static_cast<float>(this->m_texture.getSize().x);
			glyph.bounds.bottom = (float)padding / (float)this->m_texture.getSize().y;

			this->m_glyphs.insert({ c, glyph, });

			x += face->glyph->bitmap.width + (padding * 2u);
		}
		gl->GenerateMipmap(GL_TEXTURE_2D);

		this->m_texture.unbind();
		gl->PixelStorei(GL_UNPACK_ALIGNMENT, 4);

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}

	const Texture& Font::getTexture() const noexcept
	{
		return this->m_texture;
	}

	Texture& Font::getTexture() noexcept
	{
		return this->m_texture;
	}

	//TODO:
	//Search for the correct one & load it in...
	const Glyph& Font::getGlyph(const char8_t character) const noexcept
	{
		return this->m_glyphs.at(character);
	}
}