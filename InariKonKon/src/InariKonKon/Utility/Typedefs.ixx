export module Typedefs;

import <type_traits>;

export namespace ikk
{
	class Scene;
	struct VertexBase;

	struct Event
	{
		struct SizeEvent;
		struct Empty;
	};

	template<class T>
	concept SceneType = std::is_base_of<Scene, T>::value;

	template<class T>
	concept EventType = std::is_same<Event::SizeEvent, T>::value || std::is_same<Event::Empty, T>::value;

	template<class T>
	concept VertexType = std::is_base_of<VertexBase, T>::value;

	template<class T>
	concept Number = std::is_arithmetic<T>::value;
}