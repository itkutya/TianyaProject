#pragma once

#include <cstdint>
#include <cmath>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	template<priv::Number T>
	struct Vector3 final
	{
		constexpr Vector3() noexcept = default;
		constexpr Vector3(const T x, const T y, const T z) noexcept : x(x), y(y), z(z) {};

		constexpr Vector3(const Vector3&) noexcept = default;
		constexpr Vector3(Vector3&&) noexcept = default;

		constexpr Vector3& operator=(const Vector3&) noexcept = default;
		constexpr Vector3& operator=(Vector3&&) noexcept = default;

		constexpr ~Vector3() noexcept = default;

		[[nodiscard]] const float length() const noexcept
		{
			return std::sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
		};

		[[nodiscard]] constexpr Vector3<T> operator+(const Vector3<T> right) const noexcept
		{
			return Vector3<T>{ this->x + right.x, this->y + right.y, this->z + right.z };
		};

		[[nodiscard]] constexpr Vector3<T> operator-(const Vector3<T> right) const noexcept
		{
			return Vector3<T>{ this->x - right.x, this->y - right.y, this->z - right.z };
		};

		[[nodiscard]] constexpr float operator*(const Vector3<T> right) const noexcept
		{
			return this->x * right.x + this->y * right.y + this->z * right.z;
		};

		constexpr Vector3<T>& operator+=(const Vector3<T> right) noexcept
		{
			this->x = this->x + right.x;
			this->y = this->y + right.y;
			this->z = this->z + right.z;
			return *this;
		};

		constexpr Vector3<T>& operator-=(const Vector3<T> right) noexcept
		{
			this->x = this->x - right.x;
			this->y = this->y - right.y;
			this->z = this->z - right.z;
			return *this;
		};

		T x{};
		T y{};
		T z{};
	};

	using vec3f = Vector3<float>;
	using vec3d = Vector3<double>;
	using vec3i = Vector3<int>;
	using vec3u = Vector3<std::uint32_t>;

	template<priv::Number T>
	[[nodiscard]] constexpr Vector3<float> operator/(const Vector3<T> vec, const float value) noexcept
	{
		return Vector3<float>{ vec.x / value, vec.y / value, vec.z / value };
	};

	template<priv::Number T>
	[[nodiscard]] constexpr Vector3<float> operator*(const Vector3<T> vec, const float value) noexcept
	{
		return Vector3<float>{ vec.x * value, vec.y * value, vec.z * value };
	};
}