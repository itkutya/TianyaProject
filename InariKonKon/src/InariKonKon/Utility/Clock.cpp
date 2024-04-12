#include "InariKonKon/Utility/Clock.hpp"

const ikk::Time ikk::Clock::getElapsedTime() const noexcept
{
	return Time(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - this->m_startPoint));
}

const ikk::Time ikk::Clock::restart() noexcept
{
	const Time elapsed = this->getElapsedTime();
	this->m_startPoint = std::chrono::high_resolution_clock::now();
	return elapsed;
}