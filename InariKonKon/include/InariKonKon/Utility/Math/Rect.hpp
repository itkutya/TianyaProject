#pragma once

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	//TODO:
	//Finish impl...
	template<priv::Number T>
	struct Rect
	{
		T left;
		T top;
		T right;
		T bottom;
	};
}