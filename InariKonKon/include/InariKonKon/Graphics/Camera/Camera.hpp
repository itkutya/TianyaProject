#pragma once

#include <cstdint>

#include "InariKonKon/Utility/Math/Matrix.hpp"

namespace ikk
{
	class Camera
	{
	public:
		enum class Type : std::uint8_t
		{
			Orhto = 0, Perspective = 1
		};

		Camera() noexcept = default;

		Camera(const Camera&) noexcept = default;
		Camera(Camera&&) noexcept = default;

		Camera& operator=(const Camera&) noexcept = default;
		Camera& operator=(Camera&&) noexcept = default;

		~Camera() noexcept = default;
	private:
		Type m_type;
	};
}