#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

#include "InariKonKon/Graphics/PostFX/Effects/GammaCorrection.h"

ikk::priv::PostFXManager::PostFXManager(const PostEffects effects) noexcept : m_activeEffects(effects)
{
	this->reset();

	gl->GenVertexArrays(1, &quadVAO);
	gl->GenBuffers(1, &quadVBO);
	gl->BindVertexArray(quadVAO);
	gl->BindBuffer(GL_ARRAY_BUFFER, quadVBO);
	gl->BufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	gl->EnableVertexAttribArray(0);
	gl->VertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	gl->EnableVertexAttribArray(1);
	gl->VertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
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

void ikk::priv::PostFXManager::bind() noexcept
{
	if (this->m_effects.size() > 0)
		this->m_postFXBuffer.bind();
}

void ikk::priv::PostFXManager::unbind() noexcept
{
	this->m_postFXBuffer.unbind();
}

void ikk::priv::PostFXManager::render(Window& window) noexcept
{
	if (this->m_effects.size() > 0)
	{
		this->unbind();
		gl->Disable(GL_DEPTH_TEST);
		gl->Enable(GL_BLEND);
		gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//gl->ClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		//gl->Clear(GL_COLOR_BUFFER_BIT);
		gl->BindVertexArray(quadVAO);
		for (auto& effect : this->m_effects)
			effect->apply();
		gl->ActiveTexture(GL_TEXTURE0);
		gl->BindTexture(GL_TEXTURE_2D, this->m_postFXBuffer.textureColorbuffer);
		gl->DrawArrays(GL_TRIANGLES, 0, 6);
		gl->Disable(GL_BLEND);
	}
}

void ikk::priv::PostFXManager::reset() noexcept
{
	for (std::uint32_t i = 0; i < priv::PostEffectsCount; ++i)
	{
		const PostEffects effect = static_cast<PostEffects>(1U << i);
		if (this->contains(effect))
		{
			switch (effect)
			{
			case PostEffects::GammaCorrection:
				this->m_effects.emplace_back(std::make_shared<GammaCorrection>());
				break;
			case PostEffects::ColorCorrection:
				break;
			case PostEffects::Bloom:
				break;
			case PostEffects::Test:
				break;
			}
		}
	}
}

const bool ikk::priv::PostFXManager::contains(const PostEffects effect) const noexcept
{
	return (this->m_activeEffects & effect) == effect;
}