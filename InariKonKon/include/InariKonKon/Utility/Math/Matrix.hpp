#pragma once

#include <cstdint>
#include <array>
#include <cassert>

#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	template<priv::Number T, std::size_t Row, std::size_t Column>
	class Matrix final
	{
	public:
		constexpr Matrix() noexcept = default;

		constexpr Matrix(const Matrix&) noexcept = default;
		constexpr Matrix(Matrix&&) noexcept = default;

		constexpr Matrix& operator=(const Matrix&) noexcept = default;
		constexpr Matrix& operator=(Matrix&&) noexcept = default;

		constexpr ~Matrix() noexcept = default;

		[[nodiscard]] constexpr const std::array<T, Column>& operator[](const std::size_t row) const noexcept
		{
			assert(row < Row && "Out of range index!");
			return this->m_matrix.at(row);
		};

		[[nodiscard]] constexpr std::array<T, Column>& operator[](const std::size_t row) noexcept
		{
			assert(row < Row && "Out of range index!");
			return this->m_matrix.at(row);
		};
		
		[[nodiscard]] constexpr const float& at(const std::size_t row, const std::size_t column) const noexcept
		{
			assert((row < Row || column < Column) && "Out of range index!");
			return this->m_matrix.at(row).at(column); 
		};
		
		[[nodiscard]] constexpr float& at(const std::size_t row, const std::size_t column) noexcept
		{
			assert((row < Row || column < Column) && "Out of range index!");
			return this->m_matrix.at(row).at(column); 
		};
	private:
		std::array<std::array<T, Column>, Row> m_matrix{};
	};

	using mat4x4 = Matrix<float, 4, 4>;
	using mat3x3 = Matrix<float, 3, 3>;
}