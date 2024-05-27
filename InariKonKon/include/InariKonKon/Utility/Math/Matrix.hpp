#pragma once

#include <cstdint>
#include <array>
#include <cassert>

#include "InariKonKon/Utility/TypeDefs.hpp"

#include "InariKonKon/Utility/Math/Vector3.hpp"	

namespace ikk
{
	template<priv::Number T, std::size_t Row, std::size_t Column>
	class Matrix final
	{
	public:
		constexpr Matrix() noexcept = default;
		//Cave man tactic...
		constexpr Matrix(const T value) noexcept
		{
			for (std::size_t x = 0; x < Row; ++x)
				for (std::size_t y = 0; y < Column; ++y)
					(*this)[x][y] = value;
		};

		constexpr Matrix(const Matrix&) noexcept = default;
		constexpr Matrix(Matrix&&) noexcept = default;

		constexpr Matrix& operator=(const Matrix&) noexcept = default;
		constexpr Matrix& operator=(Matrix&&) noexcept = default;

		constexpr ~Matrix() noexcept = default;

		[[nodiscard]] constexpr const std::array<T, Column>& operator[](const std::size_t row) const noexcept
		{
			assert(row < Row && "Index out of range.");
			return this->m_matrix.at(row);
		};

		[[nodiscard]] constexpr std::array<T, Column>& operator[](const std::size_t row) noexcept
		{
			assert(row < Row && "Index out of range.");
			return this->m_matrix.at(row);
		};
		
		template<std::size_t R, std::size_t C>
		[[nodiscard]] constexpr const T& at() const noexcept
		{
			static_assert(R < Row && C < Column, "Index out of range.");
			return this->m_matrix.at(R).at(C); 
		};
		
		template<std::size_t R, std::size_t C>
		[[nodiscard]] constexpr T& at() noexcept
		{
			static_assert(R < Row && C < Column, "Index out of range.");
			return this->m_matrix.at(R).at(C); 
		};

		[[nodiscard]] constexpr Matrix<T, Row, Column> operator*(const Matrix<T, Row, Column>& right) const noexcept
		{
			Matrix<T, Row, Column> temp{};
			for (std::size_t x = 0; x < Row; ++x)
				for (std::size_t y = 0; y < Column; ++y)
					temp[x][y] = (*this)[x][y] * right[x][y];
			return temp;
		};

		constexpr Matrix<T, Row, Column>& operator*=(const Matrix<T, Row, Column>& right) noexcept
		{
			for (std::size_t x = 0; x < Row; ++x)
				for (std::size_t y = 0; y < Column; ++y)
					(*this)[x][y] = (*this)[x][y] * right[x][y];
			return *this;
		};
	private:
		std::array<std::array<T, Column>, Row> m_matrix{};
	};

	using mat4x4 = Matrix<float, 4, 4>;
	using mat3x3 = Matrix<float, 3, 3>;
}