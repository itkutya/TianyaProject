#pragma once

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"
#include "InariKonKon/Graphics/DrawEnums.hpp"

namespace ikk
{
	template<Draw::Dimension D = Draw::Dimension::_3D, Projection P = Projection::Perspective>
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera<P>* camera = nullptr;
		//TODO:
		//Transformation
		//Etc...
	};
}