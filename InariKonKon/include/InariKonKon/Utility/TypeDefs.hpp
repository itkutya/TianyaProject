#pragma once

#include <type_traits>

namespace ikk
{
	class Scene;

	namespace priv
	{
		template<class T>
		concept SceneType = std::is_base_of<Scene, T>::value;

		template<class T>
		concept Number = std::is_arithmetic<T>::value;
	}
}