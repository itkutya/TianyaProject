#pragma once

#include "InariKonKon/Utility/Math/MathFunc.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"

namespace ikk
{
	enum class Projection : std::uint8_t
	{
		Orhto = 0, Perspective = 1
	};

	template<Projection P = Projection::Perspective>
	class Camera
	{
	public:
		Camera(const vec3f position = vec3f(0.0f, 0.0f, 5.0f), const vec3f worldUp = vec3f(0.0f, 1.0f, 0.0f), const float yaw = -90.f, const float pitch = 0.0f) noexcept;

		Camera(const Camera&) noexcept = default;
		Camera(Camera&&) noexcept = default;

		Camera& operator=(const Camera&) noexcept = default;
		Camera& operator=(Camera&&) noexcept = default;

		~Camera() noexcept = default;

		const mat4x4 getViewMatrix() const noexcept;
		template<typename = std::enable_if_t<P == Projection::Orhto>>
		const mat4x4 getProjectionMatrix(const float left, const float top, const float right, const float bottom, const float near = 0.1f, const float far = 100.f) const noexcept;
		template<typename = std::enable_if_t<P == Projection::Perspective>>
		const mat4x4 getProjectionMatrix(const float aspect, const float near = 0.1f, const float far = 100.f) const noexcept;
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

		void update() noexcept;
	};

	template<Projection P>
	inline ikk::Camera<P>::Camera(const vec3f position, const vec3f worldUp, const float yaw, const float pitch) noexcept : m_position(position), m_worldUp(worldUp), m_yaw(yaw), m_pitch(pitch)
	{
		this->update();
	}

	template<Projection P>
	inline const ikk::mat4x4 ikk::Camera<P>::getViewMatrix() const noexcept
	{
		const vec3f dir{ normalize(vec3f{ this->m_position + this->m_direction } - this->m_position) };
		const vec3f up{ normalize(cross(dir, this->m_up)) };
		const vec3f right{ cross(up, dir) };

		mat4x4 result{ 1.f };

		result[0][0] = up.x;
		result[1][0] = up.y;
		result[2][0] = up.z;
		result[3][0] = -dot(up, this->m_position);

		result[0][1] = right.x;
		result[1][1] = right.y;
		result[2][1] = right.z;
		result[3][1] = -dot(right, this->m_position);

		result[0][2] = -dir.x;
		result[1][2] = -dir.y;
		result[2][2] = -dir.z;
		result[3][2] = dot(dir, this->m_position);

		return result;
	}

	//FIX ME!!!
	template<Projection P>
	template<typename>
	inline const mat4x4 Camera<P>::getProjectionMatrix(const float left, const float top, const float right, const float bottom, const float near, const float far) const noexcept
	{
		mat4x4 result{ 0.f };

		result[0][0] = 2.f / (right - left);

		result[1][1] = 2.f / (top - bottom);

		result[2][2] = -2.f / (far - near);

		result[3][0] = -(right + left) / (right - left);
		result[3][1] = -(top + bottom) / (top - bottom);
		result[3][2] = -(far + near) / (far - near);

		return result;
	}

	template<Projection P>
	template<typename>
	inline const mat4x4 Camera<P>::getProjectionMatrix(const float aspect, const float near, const float far) const noexcept
	{
		mat4x4 result{ 0.f };
		const float tanHalfFov = std::tanf(radian(this->m_FOV) / 2.f);

		result[0][0] = 1.f / (aspect * tanHalfFov);

		result[1][1] = 1.f / tanHalfFov;

		result[2][2] = -(far + near) / (far - near);
		result[2][3] = -1.f;

		result[3][2] = -(2.f * far * near) / (far - near);

		return result;
	}

	template<Projection P>
	inline void ikk::Camera<P>::update() noexcept
	{
		vec3f dir{};
		dir.x = cos(radian(this->m_yaw)) * cos(radian(this->m_pitch));
		dir.y = sin(radian(this->m_pitch));
		dir.z = sin(radian(this->m_yaw)) * cos(radian(this->m_pitch));
		this->m_direction = normalize(dir);

		this->m_right = normalize(cross(this->m_direction, this->m_worldUp));
		this->m_up = normalize(cross(this->m_right, this->m_direction));
	}
}