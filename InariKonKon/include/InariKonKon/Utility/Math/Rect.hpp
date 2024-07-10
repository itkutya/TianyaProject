#pragma once

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	/*
	1|
	 |
	 |
	 |
	 |
	0|---------------
	  0				1
	*/
	template<Number T>
	struct Rect
	{
		T left;
		T bottom;
		T right;
		T top;
	};

	using FloatRect = Rect<float>;
	using IntRect = Rect<int>;
	using URect = Rect<std::uint32_t>;
}