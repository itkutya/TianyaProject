#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

#include "InariKonKon/Graphics/OpenGL.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::priv::PostFXManager::PostFXManager(const Vector2<std::uint32_t> screenSize, const PostEffects effects) noexcept : RenderTexture(screenSize), m_activeEffects(effects)
{
	this->reset();
}

const ikk::PostEffects ikk::priv::PostFXManager::getActiveEffetcts() const noexcept
{
	return this->m_activeEffects;
}

void ikk::priv::PostFXManager::setEffects(const PostEffects newEffect) noexcept
{
	if (this->m_activeEffects != newEffect)
	{
		this->m_activeEffects = newEffect;
		this->reset();
	}
}

void ikk::priv::PostFXManager::render(const Window& window) const noexcept
{
	if (this->m_activeEffects != PostEffects::None)
	{
		gl->Disable(GL_DEPTH_TEST);
		gl->Enable(GL_BLEND);
		gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		window.setDefaultFrameBufferActive();

		RenderState state;
		state.applyPostFX = false;
		state.shader = this->m_effects.get();
		state.texture = &this->getFrameBuffer().getTexture();

		this->display(window, state);
	}
}

void ikk::priv::PostFXManager::reset() noexcept
{
	std::string basicVS =
R"(#version 460 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 texCoord;

out vec2 outTexCoord;

void main()
{
	gl_Position = vec4(position, 0.0, 1.0);
	outTexCoord = texCoord;
})";

	std::string basicFS =
R"(#version 460 core

out vec4 FragColor;

in vec2 outTexCoord;

layout(binding = 0) uniform sampler2D scene;

void main()
{
	vec4 color = texture(scene, outTexCoord);
)";
	for (std::uint32_t i = 0; i < priv::PostEffectsCount; ++i)
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
				basicFS += R"(	color = pow(color, vec4(1.0 / 2.2));
)";
				break;
			}
		}
	}
	basicFS += R"(	FragColor = color;
})";
	this->m_effects = std::make_unique<Shader>(basicVS.c_str(), basicFS.c_str());
}

const bool ikk::priv::PostFXManager::contains(const PostEffects effect) const noexcept
{
	return (this->m_activeEffects & effect) == effect;
}