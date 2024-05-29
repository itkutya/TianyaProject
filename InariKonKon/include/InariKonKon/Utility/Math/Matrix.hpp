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
		constexpr Matrix(const T value) noexcept : m_matrix([&value]()
			{
				std::array<std::array<T, Column>, Row> temp{};
				for (std::size_t x = 0; x < Row; ++x)
					for (std::size_t y = 0; y < Column; ++y)
						if (x == y)
							temp[x][y] = value;
				return temp; 
			}()) {};

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