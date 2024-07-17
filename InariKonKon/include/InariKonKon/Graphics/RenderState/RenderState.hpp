#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"

namespace ikk
{
	class BlendMode;

	template<Projection P>
	struct RenderState final
	{
		const Shader* shader = &Shader::getDefaultShaderProgram();
		const Texture* texture = nullptr;
		const Camera<P> *camera = nullptr;
		//const BlendMode* blendmode;
		FloatRect view = { 0.f, 0.f, 1.f, 1.f };
		bool isTransparent = false;
	};
}