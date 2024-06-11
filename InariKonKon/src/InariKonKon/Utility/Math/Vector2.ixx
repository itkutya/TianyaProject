export module Vector2;

import <cstdint>;
import <cmath>;

import Typedefs;

export namespace ikk
{
	template<Number T>
	struct Vector2 final
	{
		constexpr Vector2() noexcept = default;
		constexpr Vector2(const T x, const T y) noexcept : x(x), y(y) {};

		constexpr Vector2(const Vector2&) noexcept = default;
		constexpr Vector2(Vector2&&) noexcept = default;

		constexpr Vector2& operator=(const Vector2&) noexcept = default;
		constexpr Vector2& operator=(Vector2&&) noexcept = default;

		constexpr ~Vector2() noexcept = default;

		[[nodiscard]] const float length() const noexcept
		{
			return std::sqrtf(std::powf(this->x, 2.f) + std::powf(this->z, 2.f));
		};

		[[nodiscard]] constexpr Vector2<T> operator+(const Vector2<T> right) const noexcept
		{
			return Vector2<T>{ this->x + right.x, this->y + right.y };
		};

		[[nodiscard]] constexpr Vector2<T> operator-(const Vector2<T> right) const noexcept
		{
			return Vector2<T>{ this->x - right.x, this->y - right.y };
		};

		constexpr Vector2<T>& operator+=(const Vector2<T> right) noexcept
		{
			this->x + right.x;
			this->y + right.y;
			return *this;
		};

		constexpr Vector2<T>& operator-=(const Vector2<T> right) noexcept
		{
			this->x - right.x;
			this->y - right.y;
			return *this;
		};

		T x{};
		T y{};
	};

	using vec2f = Vector2<float>;
	using vec2d = Vector2<double>;
	using vec2i = Vector2<int>;
	using vec2u = Vector2<std::uint32_t>;

	template<Number T>
	[[nodiscard]] constexpr Vector2<float> operator/(const Vector2<T> vec, const float value) noexcept
	{
		return Vector2<float>{ vec.x / value, vec.y / value };
	};

	template<Number T>
	[[nodiscard]] constexpr Vector2<float> operator*(const Vector2<T> vec, const float value) noexcept
	{
		return Vector2<float>{ vec.x * value, vec.y * value };
	};
}