#pragma once

#include <cstdint>

namespace ikk
{
	class Event final
	{
	public:
		struct ResizeEvent
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		struct ScaleEvent
		{
			float x;
			float y;
		};

		struct PositionEvent
		{
			float x;
			float y;
		};

		struct StatusChanged
		{
			bool status;
		};

		//TODO:
		struct KeyEvent
		{

		};
		//TODO:
		struct MouseEvent
		{

		};
		//TODO:
		struct JoystickEvent
		{

		};
		//TODO:
		struct FileDropEvent
		{

		};
		//TODO:
		//Fix names...
		//& impl unions...
		//etc...
		enum class Type : std::uint8_t
		{
            WindowClosed, WindowResized, WindowFramebufferResized, WindowContentScaleChanged, WindowPositionChanged, 
            WindowIconified, WindowUnIconified, WindowMaximized, WindowUnMaximized, WindowFocused, WindowUnFocused, WindowRefreshed,
            MonitorConnected, MonitorDisconnected,
            KeyPressed, CharacterTyped, CursorPositionChanged, CursorEnteredWindow, CursorLeftWindow, MouseButtonPressed, MouseWheelScrolled, JoystickConnected, JoystickDisconnected,
            FileDropped
		};

		template<class T>
		Event(const Type type, const T data) noexcept;

		Event(const Event&) noexcept = default;
		Event(Event&) noexcept = default;
		Event(Event&&) noexcept = default;

		Event& operator=(const Event&) noexcept = default;
		Event& operator=(Event&) noexcept = default;
		Event& operator=(Event&&) noexcept = default;

		~Event() noexcept = default;
		
		Type type;
		union
		{
			bool empty = true;
			ResizeEvent size;
			ScaleEvent scale;
			PositionEvent position;
			StatusChanged status;
			KeyEvent key;
			MouseEvent mouse;
			JoystickEvent joystick;
			FileDropEvent file;
		};
	};

	//TODO:
	//Finish impl...
	template<class T>
	inline Event::Event(const Type type, const T data) noexcept : type(type)
	{
		switch (this->type)
		{
		case Event::Type::WindowFramebufferResized:
			this->size = data;
			return;
		}
	}
}