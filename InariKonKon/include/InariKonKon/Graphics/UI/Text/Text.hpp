#pragma once

#include <string_view>

#include "InariKonKon/Graphics/Drawable/Drawable.hpp"
#include "InariKonKon/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/UI/Text/Font.hpp"

namespace ikk
{
	//TODO:
	//Letterspacing?
	//etc...
	template<Dimension D = Dimension::_UI>
	class Text final : public Drawable, public Transformable<D>
	{
	public:
		Text(const std::u8string_view text, const vec3f pos = { 0.f, 0.f, 0.f }, const float scale = 1.f, const Color color = Color::White) noexcept;

		Text(const Text<D>&) noexcept = default;
		Text(Text<D>&&) noexcept = default;

		Text<D>& operator=(const Text<D>&) noexcept = default;
		Text<D>& operator=(Text<D>&&) noexcept = default;

		~Text() noexcept = default;

		void setFont(const Font& font) noexcept;

		void draw() const noexcept override;
	private:
		std::vector<Vertex> m_vertices;
		std::vector<std::uint32_t> m_indices;
		Color m_color;
		//Shader m_shader;

		const Font* m_font = nullptr;
		std::u8string_view m_text;

		void calculateVerices() noexcept;
	};

	using Text3D = Text<Dimension::_3D>;
	using Text2D = Text<Dimension::_2D>;
	using TextGUI = Text<Dimension::_UI>;

	template<Dimension D>
	Text<D>::Text(const std::u8string_view text, const vec3f pos, const float scale, const Color color) noexcept
		: Transformable<D>(pos, vec3f{ scale, scale, scale }), m_color(color), m_text(text)//, m_shader(defaultVS.c_str(), defaultFS.c_str())
	{
		this->m_vertices.reserve(text.size() * 4);
		this->m_indices.reserve(text.size() * 6);
	}

	//Fix this...
	template<Dimension D>
	void Text<D>::setFont(const Font& font) noexcept
	{
		if (this->m_font == &font)
			return;

		this->m_font = &font;
		this->calculateVerices();
	}

	template<Dimension D>
	void Text<D>::draw() const noexcept
	{
		gl->DrawElementsInstanced(GL_TRIANGLES, static_cast<GLsizei>(this->m_indices.size()), this->m_EBO.getType(), NULL, static_cast<int>(this->m_vertices.size() / 4));
	}

	template<Dimension D>
	void Text<D>::calculateVerices() noexcept
	{
		if (this->m_font == nullptr)
			return;

		this->m_vertices.clear();
		this->m_indices.clear();

		vec2f pos{ 0.f, 0.f };
		std::uint32_t indicies = 0;
		for (const char8_t character : this->m_text)
		{
			const Glyph& glyph = this->m_font->getGlyph(character);
			switch (character)
			{
			case '\0':
				break;
			case '\n':
				break;
			case '\t':
				break;
			case ' ':
				pos.x += glyph.advance.x;
				break;
			default:
				this->m_vertices.emplace_back(
					vec3f{ pos.x + glyph.bearing.x, pos.y + glyph.bearing.y, 0.f },
					this->m_color,
					vec2f{ glyph.bounds.left, glyph.bounds.bottom }
				);
				this->m_vertices.emplace_back(
					vec3f{ pos.x + glyph.bearing.x, pos.y + (glyph.bearing.y - (float)glyph.height), 0.f },
					this->m_color,
					vec2f{ glyph.bounds.left, glyph.bounds.top }
				);
				this->m_vertices.emplace_back(
					vec3f{ pos.x + glyph.bearing.x + (float)glyph.width, pos.y + glyph.bearing.y, 0.f },
					this->m_color,
					vec2f{ glyph.bounds.right, glyph.bounds.bottom }
				);
				this->m_vertices.emplace_back(
					vec3f{ pos.x + glyph.bearing.x + (float)glyph.width, pos.y + (glyph.bearing.y - (float)glyph.height), 0.f },
					this->m_color,
					vec2f{ glyph.bounds.right, glyph.bounds.top }
				);

				this->m_indices.emplace_back(indicies++);
				this->m_indices.emplace_back(indicies++);
				this->m_indices.emplace_back(indicies++);
				indicies -= 2;
				this->m_indices.emplace_back(indicies++);
				this->m_indices.emplace_back(indicies++);
				this->m_indices.emplace_back(indicies++);

				pos.x += glyph.advance.x;
				break;
			}
		}
		this->m_vertices.shrink_to_fit();
		this->m_indices.shrink_to_fit();

		this->m_VAO.setup(this->m_VBO, std::span{ this->m_vertices }, this->m_EBO, std::span{ this->m_indices });
	}
}