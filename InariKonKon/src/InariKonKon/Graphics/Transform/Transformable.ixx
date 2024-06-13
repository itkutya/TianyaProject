export module Transformable;

import Transform;
import DrawEnums;

export namespace ikk
{
	template<Dimension D = Dimension::_3D>
	class Transformable
	{
	public:
		constexpr Transformable() noexcept = default;

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