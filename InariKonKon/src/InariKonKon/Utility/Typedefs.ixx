export module InariKonKon:Typedefs;

import <type_traits>;

import :Scene;

export namespace ikk
{
	template<class T>
	concept SceneType = std::is_base_of<Scene, T>::value;

	template<class T>
	concept Number = std::is_arithmetic<T>::value;
}