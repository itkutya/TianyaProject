#pragma once

//#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"

namespace ikk
{
	template<Dimension D>
	class Transform;
	class Texture;
	template<Projection P>
	class Camera;
	//TODO:
	//Make tempaletd stuff easies to use...
	//Add opengl state stuff
	template<Dimension D = Dimension::_3D, Projection P = Projection::Perspective>
	struct RenderState final
	{
		//const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera<P>* camera = nullptr;
		const Transform<D>* transform = nullptr;
		bool isTransparent = false;
		//Blend
		//OpenGL State stuff like depth testing...
	};
}