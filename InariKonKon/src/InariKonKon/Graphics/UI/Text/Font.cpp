#include "InariKonKon/Graphics/UI/Text/Font.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"

namespace ikk
{
	Font::Font(const std::filesystem::path path)
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			throw;

		FT_Face face;
		if (FT_New_Face(ft, path.generic_string().c_str(), 0, &face))
			throw;

		FT_Set_Pixel_Sizes(face, 0, 48);

		this->m_glyphs.clear();

		gl->PixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		int atlas_width = 0;
		int atlas_height = 0;

		for (char8_t c = 0; c < 128; ++c)
		{
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				throw;

			atlas_width += face->glyph->bitmap.width;
			atlas_height = std::max(atlas_height, static_cast<int>(face->glyph->bitmap.rows));
		}
		std::uint32_t textureID;
		gl->GenTextures(1, &textureID);
		gl->BindTexture(GL_TEXTURE_2D, textureID);
		gl->TexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			atlas_width,
			atlas_height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			nullptr
		);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		gl->TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		int x = 0;

		for (char8_t c = 0; c < 128; c++)
		{
			if (FT_Load_Char(face, static_cast<char>(c), FT_LOAD_RENDER))
				throw;

			gl->TextureSubImage2D(
				textureID,
				0,
				x,
				0,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);

			Glyph glyph;

			glyph.width = face->glyph->bitmap.width;
			glyph.height = face->glyph->bitmap.rows;
			glyph.bearing = { static_cast<std::uint32_t>(face->glyph->bitmap_left), static_cast<std::uint32_t>(face->glyph->bitmap_top) };
			glyph.advance = face->glyph->advance.x;

			glyph.bounds.left = static_cast<float>(x) / static_cast<float>(atlas_width);
			glyph.bounds.top = 0.0f;
			glyph.bounds.right = static_cast<float>(x + glyph.width) / static_cast<float>(atlas_width);
			glyph.bounds.bottom = static_cast<float>(glyph.height) / static_cast<float>(atlas_height);

			this->m_glyphs.insert({ c, glyph, });

			x += face->glyph->bitmap.width;
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);
	}
}