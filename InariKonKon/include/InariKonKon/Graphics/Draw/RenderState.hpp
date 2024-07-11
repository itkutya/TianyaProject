#pragma once

#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"

namespace ikk
{
	template<Dimension D>
	class Transform;
	template<Projection P>
	class Camera;
	class Shader;
	class Texture;
	class BlendMode;

	//TODO:
	typedef Camera<> CameraObj;
	typedef Transform<> TransformObj;

	struct RenderState final
	{
		const Shader* shader = nullptr;
		const Texture* texture = nullptr;
		const CameraObj* camera = nullptr;
		const TransformObj* transform = nullptr;
		const BlendMode* blendmode;
		bool isTransparent = false;
	};
}