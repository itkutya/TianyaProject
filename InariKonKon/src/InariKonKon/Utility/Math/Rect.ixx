export module Rect;

import Typedefs;

export namespace ikk
{
	//TODO:
	//Finish impl...
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
}