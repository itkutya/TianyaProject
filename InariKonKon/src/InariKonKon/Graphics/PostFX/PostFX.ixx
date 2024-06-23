module;

#include "InariKonKon/Graphics/OpenGL.hpp"

export module PostFX;

import <memory>;
import <string>;

export import PostEffects;

import FrameBuffer;
import Context;
import Shader;
import Quad;

export namespace ikk
{
	class Window;

	class PostFX final
	{
	public:
		PostFX(const vec2u screenSize, const PostEffects effects = PostEffects::None) noexcept;

		PostFX(const PostFX&) noexcept = default;
		PostFX(PostFX&&) noexcept = default;

		PostFX& operator=(const PostFX&) noexcept = default;
		PostFX& operator=(PostFX&&) noexcept = default;

		~PostFX() noexcept = default;

		[[nodiscard]] const PostEffects getActiveEffetcts() const noexcept;
		void setEffects(const PostEffects newEffect) noexcept;

		void clear() const noexcept;
		void activate() const noexcept;
		void display(const Window& window) const noexcept;
	private:
		PostEffects m_activeEffects;
		std::unique_ptr<Shader> m_effects;

		FrameBuffer m_frameBuffer;
		Quad<ikk::Dimension::_2D> m_screen;

		[[nodiscard]] void reset() noexcept;
		[[nodiscard]] const bool contains(const PostEffects effect) const noexcept;

		void setDefaultFrameBuffer() const noexcept;
	};

	PostFX::PostFX(const vec2u screenSize, const PostEffects effects) noexcept : m_activeEffects(effects), m_frameBuffer(screenSize), m_screen(Color::White)
	{
		this->reset();
	}

	const PostEffects PostFX::getActiveEffetcts() const noexcept
	{
		return this->m_activeEffects;
	}

	void PostFX::setEffects(const PostEffects newEffect) noexcept
	{
		if (this->m_activeEffects != newEffect)
		{
			this->m_activeEffects = newEffect;
			this->reset();
		}
	}

	void PostFX::setDefaultFrameBuffer() const noexcept
	{
		gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void PostFX::clear() const noexcept
	{
		if (this->m_activeEffects != PostEffects::None)
		{
			this->m_frameBuffer.bind();
			gl->ClearColor(0.f, 0.f, 0.f, 0.f);
			gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
	}

	void PostFX::activate() const noexcept
	{
		if (this->getActiveEffetcts() != PostEffects::None)
			this->m_frameBuffer.bind();
		else
			this->m_frameBuffer.unbind();
	}

	void PostFX::display(const Window& window) const noexcept
	{
		if (this->m_activeEffects != PostEffects::None)
		{
			gl->Disable(GL_DEPTH_TEST);
			gl->Enable(GL_BLEND);
			gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			this->setDefaultFrameBuffer();

			RenderState<Dimension::_2D, Projection::Ortho> state{ .shader = this->m_effects.get(), .texture = &this->m_frameBuffer.getTexture() };
			this->m_screen.draw(window, state);
		}
	}

	void PostFX::reset() noexcept
	{
		std::string basicVS =
			R"(#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;

out vec4 outColor;
out vec2 outTexCoord;

void main()
{
	gl_Position = vec4(position, 1.0);
	outColor = color;
	outTexCoord = texCoord;
})";

		std::string basicFS =
			R"(#version 460 core

out vec4 FragColor;

in vec4 outColor;
in vec2 outTexCoord;

layout(binding = 0) uniform sampler2D scene;

void main()
{
	vec4 color = texture(scene, outTexCoord) * outColor;
)";
		for (std::uint32_t i = 0; i < PostEffectsCount; ++i)
		{
			const PostEffects effect = static_cast<PostEffects>(1U << i);
			if (this->contains(effect))
			{
				switch (effect)
				{
				case PostEffects::InvertColors:
					basicFS += R"(	color.rgb = vec3(1.0) - color.rgb;
)";
					break;
				case PostEffects::GammaCorrection:
					basicFS += R"(	color.rgb = pow(color.rgb, vec3(1.0 / 2.2));
)";
					break;
				}
			}
		}
		basicFS += R"(	FragColor = color;
})";
		this->m_effects = std::make_unique<Shader>(basicVS.c_str(), basicFS.c_str());
		this->m_effects->setTexture("scene", this->m_frameBuffer.getTexture());
	}

	const bool PostFX::contains(const PostEffects effect) const noexcept
	{
		return (this->m_activeEffects & effect) == effect;
	}
}