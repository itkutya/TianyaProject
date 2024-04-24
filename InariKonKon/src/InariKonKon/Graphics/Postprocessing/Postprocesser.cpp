#include "InariKonKon/Graphics/Postprocessing/Postprocesser.hpp"

#include "InariKonKon/Window/Window.hpp"

ikk::Postprocesser::Postprocesser(const PostEffect effects) noexcept : m_activeEffects(effects), m_postprocessing(this->reset())
{
}

const ikk::PostEffect ikk::Postprocesser::getActiveEffetcts() const noexcept
{
	return this->m_activeEffects;
}

void ikk::Postprocesser::setEffects(const PostEffect newEffect) noexcept
{
	if (this->m_activeEffects != newEffect)
	{
		this->m_activeEffects = newEffect;
		this->m_postprocessing = this->reset();
	}
}

void ikk::Postprocesser::apply(const Window& window) noexcept
{
	this->m_postprocessing.bind();
}

const ikk::Shader ikk::Postprocesser::reset() noexcept
{
	if (this->contains(PostEffect::Bloom))
	{

	}

	Shader temp("", "");
	return temp;
}

const bool ikk::Postprocesser::contains(const PostEffect effect) const noexcept
{
	return std::to_underlying(this->m_activeEffects & effect) != 0;
}