#pragma once

#include <type_traits>

namespace ikk
{
	class Scene;
	class Entity;
	class EntityComponentBase;
	struct VertexBase;
	struct Vertex;

	template<class T>
	concept SceneType = std::is_base_of<Scene, T>::value;

	template<class T>
	concept VertexType = std::is_base_of<VertexBase, T>::value || std::is_same<Vertex, T>::value;

	template<class T>
	concept Number = (std::is_floating_point<T>::value || std::is_integral<T>::value) && !std::is_same<bool, T>::value;

	template<class T>
	concept EntityType = std::is_base_of<Entity, T>::value;

	template<class T>
	concept EntityComponentType = std::is_base_of<EntityComponentBase, T>::value;
}