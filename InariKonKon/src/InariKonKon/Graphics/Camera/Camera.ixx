export module Camera;

import <cstdint>;
import <cmath>;

export import MathFuncs;
export import Vector3;
export import Matrix;
export import Rect;

import UniformBuffer;
import DrawEnums;

export namespace ikk
{
	template<Projection P = Projection::Perspective>
	class Camera
	{
	public:
		Camera(const vec3f position = vec3f(0.f, 0.f, 0.f), const vec3f worldUp = vec3f(0.f, 1.f, 0.f), const float yaw = -90.f, const float pitch = 0.f, const float near = 0.f, const float far = 100.f) noexcept;

		Camera(const Camera<P>&) noexcept = default;
		Camera(Camera<P>&&) noexcept = default;

		Camera<P>& operator=(const Camera<P>&) noexcept = default;
		Camera<P>& operator=(Camera<P>&&) noexcept = default;

		~Camera() noexcept = default;

		[[nodiscard]] const mat4x4 getViewMatrix() const noexcept;
		template<typename = std::enable_if_t<P == Projection::Ortho>>
		[[nodiscard]] const mat4x4 getProjectionMatrix(const Rect<float> viewRect) const noexcept;
		template<typename = std::enable_if_t<P == Projection::Perspective>>
		[[nodiscard]] const mat4x4 getProjectionMatrix(const float aspect) const noexcept;
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

		UniformBuffer m_uniformBuffer{};

		void update() noexcept;

		const UniformBuffer& getUniformBuffer() const noexcept;
		friend class Shader;
	};

	template<Projection P>
	Camera<P>::Camera(const vec3f position, const vec3f worldUp, const float yaw, const float pitch, const float near, const float far) noexcept
		: m_position(position), m_worldUp(worldUp), m_yaw(yaw), m_pitch(pitch), m_near(near), m_far(far)
	{
		this->update();
	}

	template<Projection P>
	const mat4x4 Camera<P>::getViewMatrix() const noexcept
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

	template<Projection P>
	template<typename>
	const mat4x4 Camera<P>::getProjectionMatrix(const Rect<float> viewRect) const noexcept
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
	void Camera<P>::update() noexcept
	{
		vec3f dir{};
		dir.x = cos(radian(this->m_yaw)) * cos(radian(this->m_pitch));
		dir.y = sin(radian(this->m_pitch));
		dir.z = sin(radian(this->m_yaw)) * cos(radian(this->m_pitch));
		this->m_direction = normalize(dir);

		this->m_right = normalize(cross(this->m_direction, this->m_worldUp));
		this->m_up = normalize(cross(this->m_right, this->m_direction));
	}

	template<Projection P>
	const UniformBuffer& Camera<P>::getUniformBuffer() const noexcept
	{
		return this->m_uniformBuffer;
	}
}