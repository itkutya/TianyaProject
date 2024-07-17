#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"

/*
namespace ikk
{
	enum class Dimension : std::uint8_t
	{
		_UI = 1, _2D = 2, _3D = 3
	};
}
*/

namespace ikk
{
	class TransformComponent : public EntityComponent<0>
	{
	public:
		[[nodiscard]] constexpr const mat4x4& getMatrix() const noexcept;
		[[nodiscard]] constexpr mat4x4& getMatrix() noexcept;

		constexpr TransformComponent& translate(const vec3f vec) noexcept;
		constexpr TransformComponent& translate(const vec2f vec) noexcept;

		constexpr TransformComponent& scale(const vec3f scale) noexcept;
	private:
		mat4x4 m_model{ 1.f };
	};

	constexpr const mat4x4& TransformComponent::getMatrix() const noexcept
	{
		return this->m_model;
	}

	constexpr mat4x4& TransformComponent::getMatrix() noexcept
	{
		return this->m_model;
	}

	constexpr TransformComponent& TransformComponent::translate(const vec3f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;
		translation[3][2] = vec.z;

		this->m_model *= translation;

		return *this;
	}

	constexpr TransformComponent& TransformComponent::translate(const vec2f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;

		this->m_model *= translation;

		return *this;
	}

	constexpr TransformComponent& TransformComponent::scale(const vec3f scale) noexcept
	{
		mat4x4 scaling(1.f);
		scaling[0][0] = scale.x;
		scaling[1][1] = scale.y;
		scaling[2][2] = scale.z;

		this->m_model *= scaling;

		return *this;
	}
}