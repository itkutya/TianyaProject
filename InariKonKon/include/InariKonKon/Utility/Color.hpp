#pragma once

namespace ikk
{
	struct Color final
	{
		constexpr Color(const float r = 0.f, const float g = 0.f, const float b = 0.f, const float a = 1.f) noexcept : r(r), g(g), b(b), a(a) {};

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