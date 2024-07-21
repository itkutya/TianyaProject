#pragma once

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"

namespace ikk
{
	class BlendMode;

	template<Projection P = Projection::None>
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera<P>* camera = nullptr;
		//const BlendMode* blendmode;
		bool isTransparent = false;
		//TODO
		//If gui -> front if not normal depth?
	};
}