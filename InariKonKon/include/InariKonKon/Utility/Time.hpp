#pragma once

#include <cstdint>
#include <chrono>
#include <cassert>

namespace ikk
{
	class Time final
	{
	public:
		constexpr Time() noexcept = default;
		template <typename Rep, typename Period>
		inline constexpr Time(const std::chrono::duration<Rep, Period>& duration) noexcept : m_value(duration) {};
		inline constexpr Time(const float amount) noexcept			: m_value(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::duration<float>(amount)))
																	{ assert((amount > 0.f) && "Time amount cannot be negative number!"); };
		inline constexpr Time(const std::uint32_t amount) noexcept	: m_value(std::chrono::milliseconds(amount)) {};
		inline constexpr Time(const std::uint64_t amount) noexcept	: m_value(std::chrono::microseconds(amount)) {};

		constexpr Time(const Time&) noexcept = default;
		constexpr Time(Time&&) noexcept = default;

		constexpr Time& operator=(const Time&) noexcept = default;
		constexpr Time& operator=(Time&&) noexcept = default;

		constexpr ~Time() noexcept = default;

		inline constexpr float asSeconds() const noexcept				{ return static_cast<float>(this->m_value.count() / 1000000.f);		};
		inline constexpr std::int32_t asMilliseconds() const noexcept	{ return static_cast<std::int32_t>(this->m_value.count() / 1000u);	};
		inline constexpr std::int64_t asMicroseconds() const noexcept	{ return this->m_value.count();										};

		inline constexpr std::chrono::microseconds toDuration() const noexcept { return this->m_value; };
	private:
		std::chrono::microseconds m_value{};
	};

	[[nodiscard]] inline constexpr Time seconds(const float amount)				 noexcept { return Time(amount); };
	[[nodiscard]] inline constexpr Time milliseconds(const std::uint32_t amount) noexcept { return Time(amount); };
	[[nodiscard]] inline constexpr Time microseconds(const std::uint64_t amount) noexcept { return Time(amount); };
}