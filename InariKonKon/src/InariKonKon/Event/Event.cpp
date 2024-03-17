#include "InariKonKon/Event/Event.hpp"

namespace ikk
{
	Event::Event(const Type type) noexcept : type(type)
	{
	}

	Event::Event(const Type type, const ResizeEvent size) noexcept : type(type), size(size)
	{
	}

	Event::Event(const Type type, const ScaleEvent scale) noexcept : type(type), scale(scale)
	{
	}

	Event::Event(const Type type, const PositionEvent position) noexcept : type(type), position(position)
	{
	}

	Event::Event(const Type type, const StatusChanged status) noexcept : type(type), status(status)
	{
	}

	Event::Event(const Type type, const KeyEvent key) noexcept : type(type), key(key)
	{
	}

	Event::Event(const Type type, const MouseEvent mouse) noexcept : type(type), mouse(mouse)
	{
	}

	Event::Event(const Type type, const JoystickEvent joystick) noexcept : type(type), joystick(joystick)
	{
	}

	Event::Event(const Type type, const FileDropEvent file) noexcept : type(type), file(file)
	{
	}
}