#pragma once

#include <cstdint>

namespace ikk
{
	class Window;
	class Time;
	class Event;
	class Application;

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
		//TODO:
		//virtual void processEvent(const Event& event) noexcept = 0;
		virtual void update(Application& app, const Time& dt) noexcept = 0;
		virtual void draw(Window& window) noexcept = 0;

		[[nodiscard]] virtual const std::uint32_t& getID() const noexcept final;
	protected:
		std::uint32_t m_id;
	};
}