#pragma once

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Color.hpp"

namespace ikk
{
	struct Vertex final
	{
		Vector3<float> position;
		Color color;
		Vector2<float> texCoord;
	};
}