#include "InariKonKon/Utility/Clock.hpp"

namespace ikk
{
	const Time Clock::getElapsedTime() const noexcept
	{
		return Time(std::chrono::steady_clock::now() - this->m_startPoint);
	}

	const Time Clock::restart() noexcept
	{
		const Time elapsed = this->getElapsedTime();
		this->m_startPoint = std::chrono::steady_clock::now();
		return elapsed;
	}
}