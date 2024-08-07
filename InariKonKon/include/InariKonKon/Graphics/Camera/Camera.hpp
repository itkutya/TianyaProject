#pragma once

#include "InariKonKon/Utility/Math/MathFuncs.hpp"
#include "InariKonKon/Utility/Math/Matrix.hpp"
#include "InariKonKon/Utility/Math/Rect.hpp"
#include "InariKonKon/Utility/Time.hpp"

//temp!!!
#include "InariKonKon/Input/Keyboard/Keyboard.hpp"

namespace ikk
{
	enum class Projection : std::uint8_t
	{
		None = 0, Ortho = 1, Perspective = 2
	};

	template<Projection P>
	class Camera
	{
	public:
		Camera(const vec3f position = vec3f(0.f, 0.f, 0.f), const vec3f worldUp = vec3f(0.f, 1.f, 0.f), const float yaw = -90.f, const float pitch = 0.f, const float near = 0.01f, const float far = 100.f) noexcept;

		Camera(const Camera<P>&) noexcept = default;
		Camera(Camera<P>&&) noexcept = default;

		Camera<P>& operator=(const Camera<P>&) noexcept = default;
		Camera<P>& operator=(Camera<P>&&) noexcept = default;

		~Camera() noexcept = default;

		[[nodiscard]] const mat4x4 getViewMatrix() const noexcept;
		template<typename = std::enable_if_t<P == Projection::Ortho>>
		[[nodiscard]] const mat4x4 getProjectionMatrix(const FloatRect viewRect) const noexcept;
		template<typename = std::enable_if_t<P == Projection::Perspective>>
		[[nodiscard]] const mat4x4 getProjectionMatrix(const float aspect) const noexcept;

		void update(const ikk::Time& dt) noexcept;
	private:
		vec3f m_position;
		vec3f m_worldUp;
		vec3f m_direction = vec3f(0.f, 0.f, -1.f);
		vec3f m_up = vec3f(0.f, 0.f, 0.f);
		vec3f m_right = vec3f(0.f, 0.f, 1.f);

		float m_yaw;
		float m_pitch;
		float m_near;
		float m_far;
		float m_FOV = 45.f;

		void updateVectors() noexcept;
	};

	template<Projection P>
	Camera<P>::Camera(const vec3f position, const vec3f worldUp, const float yaw, const float pitch, const float near, const float far) noexcept
		: m_position(position), m_worldUp(worldUp), m_yaw(yaw), m_pitch(pitch), m_near(near), m_far(far)
	{
		assert(near > 0.f && "Camera near value must be bigger then zero!");
		this->updateVectors();
	}

	template<Projection P>
	const mat4x4 Camera<P>::getViewMatrix() const noexcept
	{
		const vec3f dir{ normalize(vec3f{ this->m_position + this->m_direction } - this->m_position) };
		const vec3f up{ normalize(crossProduct(dir, this->m_up)) };
		const vec3f right{ crossProduct(up, dir) };

		mat4x4 result{ 1.f };

		result[0][0] = up.x;
		result[1][0] = up.y;
		result[2][0] = up.z;
		result[3][0] = -dotProduct(up, this->m_position);

		result[0][1] = right.x;
		result[1][1] = right.y;
		result[2][1] = right.z;
		result[3][1] = -dotProduct(right, this->m_position);

		result[0][2] = -dir.x;
		result[1][2] = -dir.y;
		result[2][2] = -dir.z;
		result[3][2] = dotProduct(dir, this->m_position);

		return result;
	}

	template<Projection P>
	template<typename>
	const mat4x4 Camera<P>::getProjectionMatrix(const FloatRect viewRect) const noexcept
	{
		mat4x4 result{ 1.f };

		result[0][0] = 2.f / (viewRect.right - viewRect.left);

		result[1][1] = 2.f / (viewRect.top - viewRect.bottom);

		result[2][2] = -2.f / (this->m_far - this->m_near);

		result[3][0] = -(viewRect.right + viewRect.left) / (viewRect.right - viewRect.left);
		result[3][1] = -(viewRect.top + viewRect.bottom) / (viewRect.top - viewRect.bottom);
		result[3][2] = -(this->m_far + this->m_near) / (this->m_far - this->m_near);

		return result;
	}

	template<Projection P>
	template<typename>
	const mat4x4 Camera<P>::getProjectionMatrix(const float aspect) const noexcept
	{
		mat4x4 result{ 0.f };
		const float tanHalfFov = std::tanf(radian(this->m_FOV) / 2.f);

		result[0][0] = 1.f / (aspect * tanHalfFov);

		result[1][1] = 1.f / tanHalfFov;

		result[2][2] = -(this->m_far + this->m_near) / (this->m_far - this->m_near);
		result[2][3] = -1.f;

		result[3][2] = -(2.f * this->m_far * this->m_near) / (this->m_far - this->m_near);

		return result;
	}

	template<Projection P>
	void Camera<P>::update(const ikk::Time& dt) noexcept
	{
		//TODO:
		//Camera movement...
		this->updateVectors();
	}

	template<Projection P>
	void Camera<P>::updateVectors() noexcept
	{
		vec3f dir{};
		dir.x = std::cos(radian(this->m_yaw)) * std::cos(radian(this->m_pitch));
		dir.y = std::sin(radian(this->m_pitch));
		dir.z = std::sin(radian(this->m_yaw)) * std::cos(radian(this->m_pitch));
		this->m_direction = normalize(dir);

		this->m_right = normalize(crossProduct(this->m_direction, this->m_worldUp));
		this->m_up = normalize(crossProduct(this->m_right, this->m_direction));
	}
}