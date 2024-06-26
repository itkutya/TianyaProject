#pragma once

#include <cstdint>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	struct Event final
	{
		class Empty final {};

		struct SizeEvent final
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		enum class Type : std::uint8_t
		{
			Empty, FrameBufferResized
		};

		template<EventType T>
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

	template<EventType T>
	Event::Event(const Event::Type type, const T data) noexcept : type(type)
	{
		switch (this->type)
		{
		case Event::Type::FrameBufferResized:
			this->size = data;
			return;
		}
		this->empty = {};
	}
}