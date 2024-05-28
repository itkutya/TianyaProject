#pragma once

#include <cstdint>

#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"
#include "InariKonKon/Utility/Time.hpp"

namespace ikk
{
	class Window;

	class Camera
	{
	public:
		enum class Type : std::uint8_t
		{
			Orhto = 0, Perspective = 1
		};

		Camera(const vec3f position = vec3f(0.0f, 0.0f, 0.0f), const vec3f worldUp = vec3f(0.0f, 1.0f, 0.0f), const float yaw = -90.f, const float pitch = 0.0f) noexcept;

		Camera(const Camera&) noexcept = default;
		Camera(Camera&&) noexcept = default;

		Camera& operator=(const Camera&) noexcept = default;
		Camera& operator=(Camera&&) noexcept = default;

		~Camera() noexcept = default;

		const mat4x4 getViewMatrix() const noexcept;
		const mat4x4 getProjectionMatrix(const float aspect = 1.f, const float near = 0.1f, const float far = 100.f) const noexcept;
		const mat4x4 getProjectionViewMatrix(const float aspect = 1.f, const float near = 0.1f, const float far = 100.f) const noexcept;

		void update(const Window& window, const Time& dt) noexcept;
	private:
		vec3f m_position;
		vec3f m_worldUp;
		vec3f m_direction = vec3f(0.0f, 0.0f, -1.0f);
		vec3f m_up = vec3f(0.0f, 0.f, 0.0f);
		vec3f m_right = vec3f(0.0f, 0.0f, 1.0f);

		float m_yaw;
		float m_pitch;

		float m_speed = 2.5f;
		float m_sensitivity = 0.1f;
		float m_FOV = 45.f;

		void updateVectors() noexcept;
	};
}