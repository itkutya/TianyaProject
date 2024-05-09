#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	struct RenderState final
	{
		Shader* shader = nullptr;
		bool applyPostFX = false;
		//TODO:
		//Texture
		//Camera
		//Transformation
		//Etc...
	};
}