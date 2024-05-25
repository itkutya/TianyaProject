#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Texture/Texture.hpp"

namespace ikk
{
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		bool applyPostFX = false;
		const Texture* texture = nullptr;
		//TODO:
		//Camera
		//Transformation
		//Etc...
	};
}