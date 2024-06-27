#pragma once

#include <type_traits>
#include <cstdint>

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

		enum class Type : std::uint8_t
		{
			Empty, FrameBufferResized
		};

		template<class T>
		Event(const Event::Type type, const T data) noexcept;
		Event(const Event::Type type) noexcept;

		Event(const Event&) noexcept = default;
		Event(Event&&) noexcept = default;

		Event& operator=(const Event&) noexcept = default;
		Event& operator=(Event&&) noexcept = default;

		~Event() noexcept = default;

		Type type;
		union
		{
			Empty empty;
			SizeEvent size;
		};
	};

	template<class T>
	Event::Event(const Event::Type type, const T data) noexcept : type(type)
	{
		static_assert(std::is_same<Event::SizeEvent, T>::value || std::is_same<Event::Empty, T>::value);
		switch (this->type)
		{
		case Event::Type::FrameBufferResized:
			this->size = data;
			return;
		}
		this->empty = {};
	}
}