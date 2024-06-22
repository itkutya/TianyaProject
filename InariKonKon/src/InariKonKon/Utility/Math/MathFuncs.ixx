export module MathFuncs;

import <cmath>;
import <numbers>;

import Typedefs;
import Vector2;
import Vector3;

export namespace ikk
{
	template<Number T>
	constexpr T radian(const T degree) noexcept
	{
		return (std::numbers::pi_v<T> / static_cast<T>(180.0)) * degree;
	};

	template<Number T>
	constexpr T degree(const T radian) noexcept
	{
		return (static_cast<T>(180.0) / std::numbers::pi_v<T>) * radian;
	};

	template<Number T>
	constexpr Vector3<T> normalize(const Vector3<T> vec) noexcept
	{
		return Vector3<T>{ vec / vec.length() };
	};

	template<Number T>
	constexpr Vector3<T> cross(const Vector3<T> left, const Vector3<T> right) noexcept
	{
		return Vector3<T>{ left.y* right.z - left.z * right.y, left.z* right.x - left.x * right.z, left.x* right.y - left.y * right.x };
	};

	template<Number T>
	constexpr float dot(const Vector3<T> left, const Vector3<T> right) noexcept
	{
		return left * right;
	};
}