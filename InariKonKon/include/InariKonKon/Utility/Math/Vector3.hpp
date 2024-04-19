#pragma once

#include <cstdint>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	template<priv::Number T>
	struct Vector3 final
	{
		constexpr Vector3() noexcept = default;
		constexpr Vector3(const T x, const T y, const T z) noexcept : x(x), y(y), z(z) {};

		constexpr Vector3(const Vector3&) noexcept = default;
		constexpr Vector3(Vector3&) noexcept = default;
		constexpr Vector3(Vector3&&) noexcept = default;

		constexpr Vector3& operator=(const Vector3&) noexcept = default;
		constexpr Vector3& operator=(Vector3&) noexcept = default;
		constexpr Vector3& operator=(Vector3&&) noexcept = default;

		constexpr ~Vector3() noexcept = default;

		T x{};
		T y{};
		T z{};
	};

	using vec3f = Vector3<float>;
	using vec3d = Vector3<double>;
	using vec3i = Vector3<int>;
	using vec3u = Vector3<std::uint32_t>;
}