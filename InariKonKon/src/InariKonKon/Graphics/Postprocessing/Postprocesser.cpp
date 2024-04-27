#include "InariKonKon/Graphics/Postprocessing/Postprocesser.hpp"

#include "InariKonKon/Window/Window.hpp"

ikk::priv::Postprocesser::Postprocesser(const PostEffect effects) noexcept : m_activeEffects(effects)
{
	this->reset();
}

const ikk::PostEffect ikk::priv::Postprocesser::getActiveEffetcts() const noexcept
{
	return this->m_activeEffects;
}

void ikk::priv::Postprocesser::setEffects(const PostEffect newEffect) noexcept
{
	if (this->m_activeEffects != newEffect)
	{
		this->m_activeEffects = newEffect;
		this->reset();
	}
}

void ikk::priv::Postprocesser::begin(const Window& window) noexcept
{
	window.setActive();
	if (this->m_effects.size() > 0)
	{
		// Bind posteffect framebuffer.
	}
}

void ikk::priv::Postprocesser::end(const Window& window) noexcept
{
	window.setActive();
	// Bind default framebuffer
	// Clear framebuffer
	for (priv::PostFX* effect : this->m_effects)
		effect->getShader().bind();
	// Draw a screen sized quad
}

void ikk::priv::Postprocesser::reset() noexcept
{
	//Order matters here!
	if (this->contains(PostEffect::Bloom))
	{
	}
	if (this->contains(PostEffect::ColorCorrection))
	{
	}
	if (this->contains(PostEffect::GammaCorrection))
	{
	}
}

const bool ikk::priv::Postprocesser::contains(const PostEffect effect) const noexcept
{
	return (this->m_activeEffects & effect) == effect;
}