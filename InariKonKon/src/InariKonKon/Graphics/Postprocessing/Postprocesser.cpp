#include "InariKonKon/Graphics/Postprocessing/Postprocesser.hpp"

#include "InariKonKon/Window/Window.hpp"

ikk::Postprocesser::Postprocesser(const PostEffect effects) noexcept 
	: m_activeEffects(effects), m_postprocessing(this->reset(effects))
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
		this->m_postprocessing = this->reset(newEffect);
	}
}

void ikk::Postprocesser::apply(const Window& window) const noexcept
{

}

const ikk::Shader ikk::Postprocesser::reset(const PostEffect newEffects) noexcept
{
	Shader temp("", "");
	return temp;
}