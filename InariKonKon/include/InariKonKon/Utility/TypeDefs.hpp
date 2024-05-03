#pragma once

#include <type_traits>

namespace ikk
{
	class Scene;

	namespace priv
	{
		template<class T>
		concept Number = std::is_arithmetic<T>::value;
	}
}