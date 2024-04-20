#pragma once

#include <cstdint>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	template<priv::Number T>
	struct Vector2 final
	{
		constexpr Vector2() noexcept = default;
		constexpr Vector2(const T x, const T y) noexcept : x(x), y(y) {};

		constexpr Vector2(const Vector2&) noexcept = default;
		constexpr Vector2(Vector2&&) noexcept = default;

		constexpr Vector2& operator=(const Vector2&) noexcept = default;
		constexpr Vector2& operator=(Vector2&&) noexcept = default;

		constexpr ~Vector2() noexcept = default;

		T x{};
		T y{};
	};

	using vec2f = Vector2<float>;
	using vec2d = Vector2<double>;
	using vec2i = Vector2<int>;
	using vec2u = Vector2<std::uint32_t>;
}