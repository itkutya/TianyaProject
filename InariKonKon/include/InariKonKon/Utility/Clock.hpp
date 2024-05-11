#pragma once

#include "InariKonKon/Utility/Time.hpp"

namespace ikk
{
	class Clock final
	{
	public:
		Clock() noexcept = default;

		Clock(const Clock&) noexcept = default;
		Clock(Clock&&) noexcept = default;

		Clock& operator=(const Clock&) noexcept = default;
		Clock& operator=(Clock&&) noexcept = default;

		~Clock() noexcept = default;

		[[nodiscard]] const Time getElapsedTime() const noexcept;
		const Time restart() noexcept;
	private:
		std::chrono::steady_clock::time_point m_startPoint = std::chrono::steady_clock::now();
	};
}