#pragma once

#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"

namespace ikk
{
	template<Dimension D = Dimension::_3D>
	class Transform final
	{
	public:
		constexpr Transform() noexcept = default;

		constexpr Transform(const Transform<D>&) noexcept = default;
		constexpr Transform(Transform<D>&&) noexcept = default;

		constexpr Transform<D>& operator=(const Transform<D>&) noexcept = default;
		constexpr Transform<D>& operator=(Transform<D>&&) noexcept = default;

		constexpr ~Transform() noexcept = default;

		[[nodiscard]] constexpr const mat4x4& getMatrix() const noexcept;
		[[nodiscard]] constexpr mat4x4& getMatrix() noexcept;
	private:
		mat4x4 m_model{ 1.f };
	};

	template<Dimension D>
	constexpr const mat4x4& Transform<D>::getMatrix() const noexcept
	{
		return this->m_model;
	}

	template<Dimension D>
	constexpr mat4x4& Transform<D>::getMatrix() noexcept
	{
		return this->m_model;
	}
}