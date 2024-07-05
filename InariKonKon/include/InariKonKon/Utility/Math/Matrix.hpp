#pragma once

#include <cassert>
#include <array>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	template<Number T, std::size_t Row, std::size_t Column>
	class Matrix final
	{
	public:
		constexpr Matrix() noexcept = default;
		constexpr Matrix(const T value) noexcept
		{
			for (std::size_t i = 0; i < ((Row < Column) ? Row : Column); ++i)
				(*this)[i][i] = value;
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

		[[nodiscard]] constexpr const T& at(const std::size_t row, const std::size_t column) const noexcept
		{
			assert((row < Row && column < Column) && "Index out of range.");
			return this->m_matrix.at(row).at(column);
		};

		[[nodiscard]] constexpr T& at(const std::size_t row, const std::size_t column) noexcept
		{
			assert((row < Row && column < Column) && "Index out of range.");
			return this->m_matrix.at(row).at(column);
		};

		[[nodiscard]] constexpr Matrix<T, Row, Column>& operator*(const Matrix<T, Row, Column> right) noexcept
		{
			for (int i = 0; i < Row; i++)
			{
				for (int j = 0; j < Column; j++)
				{
					T result{};
					for (int k = 0; k < Row; k++)
					{
						result += (*this)[i][k] * right[k][j];
					}
					(*this)[i][j] = result;
				}
			}
			return *this;
		};

		constexpr Matrix<T, Row, Column>& operator*=(const Matrix<T, Row, Column> right) noexcept
		{
			*this = *this * right;
			return *this;
		};
	private:
		std::array<std::array<T, Column>, Row> m_matrix{};
	};

	using mat4x4 = Matrix<float, 4, 4>;
	using mat3x3 = Matrix<float, 3, 3>;
}