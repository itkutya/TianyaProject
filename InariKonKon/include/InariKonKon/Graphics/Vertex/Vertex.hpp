#pragma once

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Color.hpp"

namespace ikk
{
	struct VertexBase {};

	struct Vertex : public VertexBase
	{
		vec3f position;
		Color color;
		vec2f texCoord;
	};
}