#pragma once

#include <string_view>

#include "InariKonKon/Graphics/Transform/Transformable.hpp"
#include "InariKonKon/Graphics/Draw/Drawable.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/UI/Text/Font.hpp"
#include "InariKonKon/Window/Window.hpp"

//Temp...
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_2D>
	class Text final : public Drawable<D>, public Transformable<D>
	{
	public:
		Text(const std::u8string_view text) noexcept;

		Text(const Text<D>&) noexcept = default;
		Text(Text<D>&&) noexcept = default;

		Text<D>& operator=(const Text<D>&) noexcept = default;
		Text<D>& operator=(Text<D>&&) noexcept = default;

		~Text() noexcept = default;

		void setFont(const Font& font) noexcept;

		void draw(const Window& window, RenderState<D, Projection::Ortho>& state, const FloatRect viewRect = { -1.f, -1.f, 1.f, 1.f }) const noexcept override;
		void draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept override;
	private:
		const Font* m_font = nullptr;
		std::vector<QuadGUI> m_characters;
		Shader m_shader;
		std::u8string_view m_text;
	};

	using Text3D = Text<Dimension::_3D>;
	using Text2D = Text<Dimension::_2D>;
	using TextGUI = Text<Dimension::_GUI>;

	inline static const std::string defaultVS =
		R"(#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 outColor;
out vec2 outTexCoord;

layout (std140, binding = 0) uniform Camera
{
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    outColor = color;
    outTexCoord = texCoord;
})";

	inline static const std::string defaultFS =
		R"(#version 460 core

out vec4 FragColor;

in vec4 outColor;
in vec2 outTexCoord;

layout(binding = 0) uniform sampler2D tex;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, outTexCoord).r);
    FragColor = vec4(outColor.rgb, 1.0) * sampled;
})";

	template<Dimension D>
	Text<D>::Text(const std::u8string_view text) noexcept : m_text(text), m_shader(defaultVS.c_str(), defaultFS.c_str())
	{
		this->m_characters.reserve(text.size());
	}

	template<Dimension D>
	void Text<D>::setFont(const Font& font) noexcept
	{
		if (this->m_font == &font)
			return;

		this->m_font = &font;
		this->m_characters.clear();
		for (std::size_t i = 0; i < this->m_text.size(); ++i)
			this->m_characters.emplace_back(Color::White, this->m_font->getGlyph(this->m_text.at(i)).bounds);
	}

	template<Dimension D>
	void Text<D>::draw(const Window& window, RenderState<D, Projection::Ortho>& state, const FloatRect viewRect) const noexcept
	{
		if (this->m_font == nullptr)
			return;

		for (const QuadGUI& quad : this->m_characters)
		{
			state.shader = &this->m_shader;
			state.texture = &this->m_font->getTexture();
			quad.draw(window, state, viewRect);
		}
	}

	template<Dimension D>
	void Text<D>::draw(const Window& window, RenderState<D, Projection::Perspective>& state) const noexcept
	{
		if (this->m_font == nullptr)
			return;

		for (const QuadGUI& quad : this->m_characters)
		{
			state.shader = &this->m_shader;
			state.texture = &this->m_font->getTexture();
			window.draw(quad, state);
		}
	}
}