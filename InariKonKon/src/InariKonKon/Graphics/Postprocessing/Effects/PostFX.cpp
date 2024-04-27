#include "InariKonKon/Graphics/Postprocessing/Effects/PostFX.hpp"

ikk::priv::PostFX::PostFX(const char* vertex, const char* fragment) noexcept : m_shader(vertex, fragment)
{
}

const ikk::Shader& ikk::priv::PostFX::getShader() const noexcept
{
	return this->m_shader;
}

ikk::Shader& ikk::priv::PostFX::getShader() noexcept
{
	return this->m_shader;
}