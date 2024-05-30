#pragma once

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"
#include "InariKonKon/Graphics/DrawEnums.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_3D, Projection P = Projection::Perspective>
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera<P>* camera = nullptr;
		bool isTransparent = false;
		//TODO:
		//Transformation
		//Etc...
	};
}