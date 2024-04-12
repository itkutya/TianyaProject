#pragma once

#include <cstdint>

namespace ikk
{
	struct Event final
	{
		struct SizeEvent
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		enum class Type : std::uint8_t
		{
			Empty, FrameBufferResized
		};

		template<class T>
		Event(const Type type, const T data) noexcept;
		Event(const Type type) noexcept : type(type), empty(true) {};

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
			bool empty;
			SizeEvent size;
		};
	};

	template<class T>
	inline Event::Event(const Type type, const T data) noexcept : type(type)
	{
		switch (this->type)
		{
		case Event::Type::FrameBufferResized:
			this->size = data;
			return;
		default:
			this->empty = true;
			return;
		}
	}
}