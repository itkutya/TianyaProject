#pragma once

#include <type_traits>
#include <cstdint>

#include "InariKonKon/Input/Keyboard/Keyboard.hpp"

namespace ikk
{
	struct Event final
	{
		struct Empty final {};

		struct SizeEvent final
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		struct KeyboardEvent
		{
			Keyboard::KeyCode keycode;
			Keyboard::ScanCode scancode;
		};

		enum class Type : std::uint8_t
		{
			Empty, FrameBufferResized, KeyDown, KeyUp, KeyHeld
		};

		template<class T>
		constexpr Event(const Event::Type type, const T data) noexcept;
		constexpr Event(const Event::Type type) noexcept;

		constexpr Event(const Event&) noexcept = default;
		constexpr Event(Event&&) noexcept = default;

		constexpr Event& operator=(const Event&) noexcept = default;
		constexpr Event& operator=(Event&&) noexcept = default;

		constexpr ~Event() noexcept = default;

		Type type;
		union
		{
			Empty empty;
			SizeEvent size;
			KeyboardEvent keyboard;
		};
	};

	constexpr Event::Event(const Event::Type type) noexcept : type(type), empty({})
	{
	}

	template<class T>
	constexpr Event::Event(const Event::Type type, const T data) noexcept : type(type)
	{
		static_assert(std::is_same<Event::SizeEvent, T>::value || std::is_same<Event::Empty, T>::value || std::is_same<Event::KeyboardEvent, T>::value);

		if constexpr (std::is_same<Event::SizeEvent, T>::value)
			this->size = data;
		else if constexpr (std::is_same<Event::KeyboardEvent, T>::value)
			this->keyboard = data;
		else
			this->empty = {};
	}
}