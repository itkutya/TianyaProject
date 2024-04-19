#pragma once

#include <cstdint>

namespace ikk
{
	struct Color final
	{
		constexpr Color() noexcept = default;
		constexpr Color(const float r, const float g, const float b, const float a = 1.f) noexcept 
			: r(r), g(g), b(b), a(a) {};
		constexpr Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = UINT8_MAX) noexcept
			: r(static_cast<float>(r / UINT8_MAX)), g(static_cast<float>(g / UINT8_MAX)), b(static_cast<float>(b / UINT8_MAX)), a(static_cast<float>(a / UINT8_MAX)) {};

		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr Color& operator=(const Color&) noexcept = default;
		constexpr Color& operator=(Color&) noexcept = default;
		constexpr Color& operator=(Color&&) noexcept = default;

		constexpr ~Color() noexcept = default;

		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 1.f;
	};
}