#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	struct RenderState final
	{
		Shader* shader = nullptr;
		//TODO:
		//Texture
		//Camera
		//Transformation
		//Etc...
	};
}