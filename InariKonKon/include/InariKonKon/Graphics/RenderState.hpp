#pragma once

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"

namespace ikk
{
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera* camera = nullptr;
		//TODO:
		//Transformation
		//Etc...
	};
}