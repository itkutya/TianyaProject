#pragma once

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	//TODO:
	//Finish impl...
	//OpenGL uses different stuff...
	template<Number T>
	struct Rect
	{
		T left;
		T top;
		T right;
		T bottom;
	};

	using FloatRect = Rect<float>;
	using IntRect = Rect<int>;
	using URect = Rect<std::uint32_t>;
}