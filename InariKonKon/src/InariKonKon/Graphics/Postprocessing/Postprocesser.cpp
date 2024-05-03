#include "InariKonKon/Graphics/Postprocessing/Postprocesser.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
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
	if (this->m_effects.size() > 0)
	{
		window.setActive();
		this->m_postFXBuffer.bind();
	}
}

void ikk::priv::Postprocesser::end(const Window& window) noexcept
{
	if (this->m_effects.size() > 0)
	{
		window.setActive();
		this->m_postFXBuffer.unbind();
		gl->Disable(GL_DEPTH_TEST);
		gl->ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		gl->Clear(GL_COLOR_BUFFER_BIT);
		for (auto& effect : this->m_effects)
			effect->getShader().bind();
		// use the color attachment texture as the texture of the quad plane
		window.draw(this->m_screen, this->m_state);
	}
}

void ikk::priv::Postprocesser::reset() noexcept
{
	for (std::uint32_t i = 0; i < priv::PostEffectsCount; ++i)
	{
		if (this->contains(static_cast<PostEffect>(1U << i)))
		{
			std::printf("Active effects: %i\n", static_cast<int>(static_cast<PostEffect>(1U << i)));
		}
	}
}

const bool ikk::priv::Postprocesser::contains(const PostEffect effect) const noexcept
{
	return (this->m_activeEffects & effect) == effect;
}