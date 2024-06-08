#pragma once

#include "InariKonKon/Graphics/Transform/Transform.hpp"
#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"
#include "InariKonKon/Graphics/DrawEnums.hpp"

namespace ikk
{
	//TODO:
	//Make tempaletd stuff easies to use...
	//Add opengl state stuff
	template<Dimension D = Dimension::_3D, Projection P = Projection::Perspective>
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera<P>* camera = nullptr;
		const Transform<D>* transform = nullptr;
		bool isTransparent = false;
		//Blend
		//OpenGL State stuff like depth testing...
	};
}