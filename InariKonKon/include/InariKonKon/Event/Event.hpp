#pragma once

#include <cstdint>

namespace ikk
{
	class Event final
	{
	public:
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

		Event(const Event&) noexcept = default;
		Event(Event&) noexcept = default;
		Event(Event&&) noexcept = default;

		Event& operator=(const Event&) noexcept = default;
		Event& operator=(Event&) noexcept = default;
		Event& operator=(Event&&) noexcept = default;

		~Event() noexcept = default;

		const Type& getType() const noexcept;
	private:
		Type m_type;
	};
}