#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

ikk::priv::PostFXManager::PostFXManager(const PostEffects effects) noexcept : m_activeEffects(effects)
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

void ikk::priv::PostFXManager::bind() noexcept
{
	if (this->m_effects.size() > 0)
		this->m_postFXBuffer.bind();
}

void ikk::priv::PostFXManager::unbind() noexcept
{
	this->m_postFXBuffer.unbind();
}

/*
void ikk::priv::PostFXManager::end(const Window& window) noexcept
{
	if (this->m_effects.size() > 0)
	{
		window.setActive();
		this->m_postFXBuffer.unbind();
		gl->Disable(GL_DEPTH_TEST);
		gl->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl->Clear(GL_COLOR_BUFFER_BIT);
		for (auto& effect : this->m_effects)
			effect->apply();
		// use the color attachment texture as the texture of the quad plane
		window.draw(this->m_screen);
	}
}
*/

void ikk::priv::PostFXManager::reset() noexcept
{
	for (std::uint32_t i = 0; i < priv::PostEffectsCount; ++i)
	{
		if (this->contains(static_cast<PostEffects>(1U << i)))
		{
			std::printf("Active effects: %i\n", static_cast<int>(static_cast<PostEffects>(1U << i)));
		}
	}
}

const bool ikk::priv::PostFXManager::contains(const PostEffects effect) const noexcept
{
	return (this->m_activeEffects & effect) == effect;
}