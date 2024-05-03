#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"

namespace ikk
{
	struct RenderState final
	{
		Shader* shader = nullptr;
		//TODO:
		//Decide...
		bool applyPostFX = false;
		//TODO:
		//Texture
		//Camera
		//Transformation
		//Etc...
	};
}