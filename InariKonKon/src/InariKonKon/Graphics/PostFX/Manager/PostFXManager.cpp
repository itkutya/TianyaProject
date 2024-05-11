#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"

#include "InariKonKon/Window/Context/Context.hpp"
#include "InariKonKon/Window/Window.hpp"

#include "InariKonKon/Graphics/PostFX/Effects/GammaCorrection.hpp"

ikk::priv::PostFXManager::PostFXManager(const Vector2<std::uint32_t> screenSize, const PostEffects effects) noexcept
	: RenderTexture(screenSize), m_activeEffects(effects)
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
	if (this->m_effects.size() > 0)
	{
		gl->Disable(GL_DEPTH_TEST);
		gl->Enable(GL_BLEND);
		gl->BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//for (auto& effect : this->m_effects)
		//	effect->apply();

		RenderState state;
		state.applyPostFX = false;
		state.shader = &this->m_effects.at(0)->m_shader;
		state.texture = this->getFrameBuffer().textureColorbuffer;

		this->display(window, state);
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