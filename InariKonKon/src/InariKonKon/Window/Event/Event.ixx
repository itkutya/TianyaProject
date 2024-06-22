export module Event;

import <cstdint>;

import Typedefs;

export namespace ikk
{
	struct Event final
	{
		class Empty final {};

		struct SizeEvent
		{
			std::uint32_t width;
			std::uint32_t height;
		};

		enum class Type : std::uint8_t
		{
			Empty, FrameBufferResized
		};

		template<EventType T>
		inline Event(const Type type, const T data) noexcept;
		inline Event(const Type type) noexcept;

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
	//Error is visual only...
	template<EventType T>
	inline Event::Event(const Type type, const T data) noexcept
	{
		switch (this->type)
		{
		case Event::Type::FrameBufferResized:
			this->size = data;
			return;
		}
		this->empty = {};
	}
	//Error is visual only...
	inline Event::Event(const Type type) noexcept : type(type), empty({})
	{

	}
}