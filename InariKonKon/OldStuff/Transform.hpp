#pragma once

#include "InariKonKon/Graphics/Draw/DrawEnums.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"
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

		constexpr Transform& translate(const vec3f vec) noexcept;
		constexpr Transform& translate(const vec2f vec) noexcept;

		constexpr Transform& scale(const vec3f scale) noexcept;
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

	template<Dimension D>
	constexpr Transform<D>& Transform<D>::translate(const vec3f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;
		translation[3][2] = vec.z;

		this->m_model *= translation;
		
		return *this;
	}

	template<Dimension D>
	constexpr Transform<D>& Transform<D>::translate(const vec2f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;

		this->m_model *= translation;

		return *this;
	}

	template<Dimension D>
	constexpr Transform<D>& Transform<D>::scale(const vec3f scale) noexcept
	{
		mat4x4 scaling(1.f);
		scaling[0][0] = scale.x;
		scaling[1][1] = scale.y;
		scaling[2][2] = scale.z;

		this->m_model *= scaling;

		return *this;
	}
}