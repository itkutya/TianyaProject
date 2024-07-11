#pragma once

#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"

namespace ikk
{
	template<Projection P>
	class Camera;
	class Shader;
	class Texture;
	class BlendMode;

	template<Projection P = Projection::None>
	struct RenderState final
	{
		const Shader* shader = nullptr;
		const Texture* texture = nullptr;
		const Camera<P> *camera = nullptr;
		//const BlendMode* blendmode;
		bool isTransparent = false;
	};
}