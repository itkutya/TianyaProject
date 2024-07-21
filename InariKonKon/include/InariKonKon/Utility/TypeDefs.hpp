#pragma once

#include <type_traits>

namespace ikk
{
	class Scene;
	struct VertexBase;
	struct Vertex;
	class Drawable;

	namespace priv
	{
		class EntityComponentBase;
	}

	template<class T>
	concept SceneType = std::is_base_of<Scene, T>::value;

	template<class T>
	concept VertexType = std::is_base_of<VertexBase, T>::value || std::is_same<Vertex, T>::value;

	template<class T>
	concept Number = std::is_arithmetic<T>::value && !std::is_same<bool, T>::value;

	template<class T>
	concept EntityComponentType = std::is_base_of<priv::EntityComponentBase, T>::value;

	template<class T>
	concept DrawableType = std::is_base_of<Drawable, T>::value;
}