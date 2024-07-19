#include "InariKonKon/Transform/Transform.hpp"

namespace ikk
{
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