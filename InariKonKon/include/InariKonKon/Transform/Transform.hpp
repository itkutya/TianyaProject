#pragma once

#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"

namespace ikk
{
	class Transform final
	{
	public:
		constexpr Transform() noexcept = default;

		constexpr Transform(const Transform&) noexcept = default;
		constexpr Transform(Transform&&) noexcept = default;

		constexpr Transform& operator=(const Transform&) noexcept = default;
		constexpr Transform& operator=(Transform&&) noexcept = default;

		constexpr ~Transform() noexcept = default;

		[[nodiscard]] constexpr const mat4x4& getMatrix() const noexcept;
		[[nodiscard]] constexpr mat4x4& getMatrix() noexcept;

		constexpr Transform& translate(const vec3f vec) noexcept;
		constexpr Transform& translate(const vec2f vec) noexcept;

		constexpr Transform& scale(const vec3f scale) noexcept;
	private:
		mat4x4 m_model{ 1.f };
	};

	constexpr const mat4x4& Transform::getMatrix() const noexcept
	{
		return this->m_model;
	}

	constexpr mat4x4& Transform::getMatrix() noexcept
	{
		return this->m_model;
	}

	constexpr Transform& Transform::translate(const vec3f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;
		translation[3][2] = vec.z;

		this->m_model *= translation;

		return *this;
	}

	constexpr Transform& Transform::translate(const vec2f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;

		this->m_model *= translation;

		return *this;
	}

	constexpr Transform& Transform::scale(const vec3f scale) noexcept
	{
		mat4x4 scaling(1.f);
		scaling[0][0] = scale.x;
		scaling[1][1] = scale.y;
		scaling[2][2] = scale.z;

		this->m_model *= scaling;

		return *this;
	}
}