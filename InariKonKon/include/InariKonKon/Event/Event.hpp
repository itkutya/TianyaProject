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

		Event(const Type type) noexcept;
		Event(const Type type, const ResizeEvent size) noexcept;
		Event(const Type type, const ScaleEvent scale) noexcept;
		Event(const Type type, const PositionEvent position) noexcept;
		Event(const Type type, const StatusChanged status) noexcept;
		Event(const Type type, const KeyEvent key) noexcept;
		Event(const Type type, const MouseEvent mouse) noexcept;
		Event(const Type type, const JoystickEvent joystick) noexcept;
		Event(const Type type, const FileDropEvent file) noexcept;

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
}