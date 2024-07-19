#pragma once

#include "InariKonKon/Transform/Transform.hpp"

namespace ikk
{
	enum class Dimension : std::uint8_t
	{
		_UI = 1, _2D = 2, _3D = 3
	};

	template<Dimension D = Dimension::_3D>
	class Transformable
	{
	public:
		constexpr Transformable() noexcept = default;
		constexpr Transformable(const vec3f pos, const vec2f size) noexcept;
		constexpr Transformable(const vec3f pos, const vec3f size) noexcept;

		constexpr Transformable(const Transformable<D>&) noexcept = default;
		constexpr Transformable(Transformable<D>&&) noexcept = default;

		constexpr Transformable<D>& operator=(const Transformable<D>&) noexcept = default;
		constexpr Transformable<D>& operator=(Transformable<D>&&) noexcept = default;

		virtual constexpr ~Transformable() noexcept = default;

		[[nodiscard]] virtual constexpr const Transform& getTransform() const noexcept final;
		[[nodiscard]] virtual constexpr Transform& getTransform() noexcept final;

		[[nodiscard]] virtual constexpr const mat4x4& getTransformMatrix() const noexcept final;
		[[nodiscard]] virtual constexpr mat4x4& getTransformMatrix() noexcept final;
	private:
		Transform m_transform;
	};

	template<Dimension D>
	constexpr Transformable<D>::Transformable(const vec3f pos, const vec2f size) noexcept
	{
		this->m_transform.scale({ size.x, size.y, 1.f });
		//rotaton comes now...
		this->m_transform.translate(pos);
	}

	template<Dimension D>
	constexpr Transformable<D>::Transformable(const vec3f pos, const vec3f size) noexcept
	{
		this->m_transform.scale(size);
		//rotaton comes now...
		this->m_transform.translate(pos);
	}

	template<Dimension D>
	constexpr const Transform& Transformable<D>::getTransform() const noexcept
	{
		return this->m_transform;
	}

	template<Dimension D>
	constexpr Transform& Transformable<D>::getTransform() noexcept
	{
		return this->m_transform;
	}

	template<Dimension D>
	constexpr const mat4x4& Transformable<D>::getTransformMatrix() const noexcept
	{
		return this->m_transform.getMatrix();
	}

	template<Dimension D>
	constexpr mat4x4& Transformable<D>::getTransformMatrix() noexcept
	{
		return this->m_transform.getMatrix();
	}
}