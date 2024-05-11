#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		bool applyPostFX = false;
		std::uint32_t texture = 0;
		//TODO:
		//Texture
		//Camera
		//Transformation
		//Etc...
	};
}