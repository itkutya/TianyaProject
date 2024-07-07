#pragma once

#include "InariKonKon/Graphics/Transform/Transform.hpp"

namespace ikk
{
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

		[[nodiscard]] virtual constexpr const Transform<D>& getTransform() const noexcept final;
		[[nodiscard]] virtual constexpr Transform<D>& getTransform() noexcept final;

		[[nodiscard]] virtual constexpr const mat4x4& getTransformMatrix() const noexcept final;
		[[nodiscard]] virtual constexpr mat4x4& getTransformMatrix() noexcept final;
	private:
		Transform<D> m_transform;
	};

	template<Dimension D>
	constexpr Transformable<D>::Transformable(const vec3f pos, const vec2f size) noexcept : m_transform(Transform<D>().scale({ size.x, size.y, 1.f }).translate(pos))
	{
	}

	template<Dimension D>
	constexpr Transformable<D>::Transformable(const vec3f pos, const vec3f size) noexcept : m_transform(Transform<D>().scale(size).translate(pos))
	{
	}

	template<Dimension D>
	constexpr const Transform<D>& Transformable<D>::getTransform() const noexcept
	{
		return this->m_transform;
	}

	template<Dimension D>
	constexpr Transform<D>& Transformable<D>::getTransform() noexcept
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