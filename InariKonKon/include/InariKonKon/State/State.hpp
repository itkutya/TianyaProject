#pragma once

#include <cstdint>

namespace ikk
{
	class Window;
	class Time;
	class Event;

	class State
	{
	public:
		State() noexcept;

		State(const State&) noexcept = default;
		State(State&) noexcept = default;
		State(State&&) noexcept = default;

		State& operator=(const State&) noexcept = default;
		State& operator=(State&) noexcept = default;
		State& operator=(State&&) noexcept = default;

		virtual ~State() noexcept = default;

		virtual void processEvent(const Event& event) noexcept = 0;
		virtual void update(const Time& dt) noexcept = 0;
		virtual void draw(const Window& window) noexcept = 0;

		[[nodiscard]] virtual const std::uint32_t& getID() const noexcept final;
	protected:
		std::uint32_t m_id;
	};
}