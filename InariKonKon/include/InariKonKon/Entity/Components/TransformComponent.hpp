#pragma once

#include "InariKonKon/Entity/Components/EntityComponentBase.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"

namespace ikk
{
	enum class Dimension : std::uint8_t
	{
		_UI = 1, _2D = 2, _3D = 3
	};
}

namespace ikk
{
	template<Dimension D>
	class TransformComponent : public EntityComponent<0>
	{
		[[nodiscard]] constexpr const mat4x4& getMatrix() const noexcept;
		[[nodiscard]] constexpr mat4x4& getMatrix() noexcept;

		constexpr TransformComponent& translate(const vec3f vec) noexcept;
		constexpr TransformComponent& translate(const vec2f vec) noexcept;

		constexpr TransformComponent& scale(const vec3f scale) noexcept;
	public:
		mat4x4 m_model{ 1.f };
	};

	using Transform2DComponent = TransformComponent<Dimension::_2D>;
	using Transform3DComponent = TransformComponent<Dimension::_3D>;
	using TransformUIComponent = TransformComponent<Dimension::_UI>;

	template<Dimension D>
	constexpr const mat4x4& TransformComponent<D>::getMatrix() const noexcept
	{
		return this->m_model;
	}

	template<Dimension D>
	constexpr mat4x4& TransformComponent<D>::getMatrix() noexcept
	{
		return this->m_model;
	}

	template<Dimension D>
	constexpr TransformComponent<D>& TransformComponent<D>::translate(const vec3f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;
		translation[3][2] = vec.z;

		this->m_model *= translation;

		return *this;
	}

	template<Dimension D>
	constexpr TransformComponent<D>& TransformComponent<D>::translate(const vec2f vec) noexcept
	{
		mat4x4 translation(1.f);
		translation[3][0] = vec.x;
		translation[3][1] = vec.y;

		this->m_model *= translation;

		return *this;
	}

	template<Dimension D>
	constexpr TransformComponent<D>& TransformComponent<D>::scale(const vec3f scale) noexcept
	{
		mat4x4 scaling(1.f);
		scaling[0][0] = scale.x;
		scaling[1][1] = scale.y;
		scaling[2][2] = scale.z;

		this->m_model *= scaling;

		return *this;
	}
}