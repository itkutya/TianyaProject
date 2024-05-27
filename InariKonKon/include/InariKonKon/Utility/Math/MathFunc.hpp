#pragma once

#include <cmath>
#include <numbers>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	constexpr float radian(const float degree) noexcept
	{
		return (std::numbers::pi_v<float> / 180.f) * degree;
	};

	constexpr float degree(const float radian) noexcept
	{
		return (180.f / std::numbers::pi_v<float>) * radian;
	};

	template<priv::Number T>
	constexpr Vector3<T> normalize(const Vector3<T> vec) noexcept
	{
		return Vector3<T>{ vec / vec.length() };
	};

	template<priv::Number T>
	constexpr Vector3<T> cross(const Vector3<T> left, const Vector3<T> right) noexcept
	{
		return Vector3<T>{ (left.y * right.z) - (left.z * right.y), (left.z * right.x) - (left.x * right.z), (left.x * right.y) - (left.y * right.x) };
	};

	template<priv::Number T>
	constexpr float dot(const Vector3<T> left, const Vector3<T> right) noexcept
	{
		return (left.x * right.x) + (left.y * right.y) + (left.z + right.z);
	};
}