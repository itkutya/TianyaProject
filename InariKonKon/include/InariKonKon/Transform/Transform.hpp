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
}