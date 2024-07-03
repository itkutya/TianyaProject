#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/UI/Text/Glyph.hpp"

namespace ikk
{
	class Font
	{
	public:
		Font(const std::filesystem::path path);

		Font(const Font&) noexcept = default;
		Font(Font&&) noexcept = default;

		Font& operator=(const Font&) noexcept = default;
		Font& operator=(Font&&) noexcept = default;

		const Texture& getTexture() const noexcept;
		Texture& getTexture() noexcept;

		const Glyph& getGlyph(const char8_t character) const noexcept;
	private:
		Texture m_texture;
		std::uint32_t m_width = 0;
		std::uint32_t m_height = 0;
		std::unordered_map<char8_t, Glyph> m_glyphs;
	};
}