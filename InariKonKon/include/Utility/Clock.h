#pragma once

#include "Time.h"

namespace ikk
{
	class Clock final
	{
	public:
		Clock() noexcept = default;

		Clock(const Clock&) noexcept = default;
		Clock(Clock&) noexcept = default;
		Clock(Clock&&) noexcept = default;

		Clock& operator=(const Clock&) noexcept = default;
		Clock& operator=(Clock&) noexcept = default;
		Clock& operator=(Clock&&) noexcept = default;

		~Clock() noexcept = default;

		const Time getElapsedTime() const noexcept;
		const Time restart() noexcept;
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_startPoint = std::chrono::steady_clock::now();
	};
}