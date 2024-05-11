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
	private:
		std::array<std::array<T, Column>, Row> m_matrix{};
	};

	using mat4x4 = Matrix<float, 4, 4>;
	using mat3x3 = Matrix<float, 3, 3>;
}