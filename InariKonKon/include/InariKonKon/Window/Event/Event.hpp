#pragma once

#include <cstdint>
#include <utility>

namespace ikk
{
	namespace priv
	{
		class Empty {};
	}

	struct Event final
	{
		struct SizeEvent
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		enum class Projection : std::uint8_t
		{
			Empty, FrameBufferResized
		};

		template<class T>
		Event(const Projection type, const T data) noexcept;
		Event(const Projection type) noexcept : type(type), empty({}) {};

		Event(const Event&) noexcept = default;
		Event(Event&&) noexcept = default;

		Event& operator=(const Event&) noexcept = default;
		Event& operator=(Event&&) noexcept = default;

		~Event() noexcept = default;

		Projection type;
		union
		{
			priv::Empty empty;
			SizeEvent size;
		};
	};

	template<class T>
	inline Event::Event(const Projection type, const T data) noexcept : type(type)
	{
		switch (this->type)
		{
		case Event::Projection::FrameBufferResized:
			this->size = data;
			return;
		}
		std::unreachable();
	}
}