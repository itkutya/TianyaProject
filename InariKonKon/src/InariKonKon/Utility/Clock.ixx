module;
//Some cpp libs are still messed up...
#include <chrono>

export module InariKonKon:Clock;

export import :Time;

export namespace ikk
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

	const Time Clock::getElapsedTime() const noexcept
	{
		return Time(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - this->m_startPoint));
	}

	const Time Clock::restart() noexcept
	{
		const Time elapsed = this->getElapsedTime();
		this->m_startPoint = std::chrono::steady_clock::now();
		return elapsed;
	}
}