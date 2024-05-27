#include "InariKonKon/Graphics/Camera/Camera.hpp"

#include "InariKonKon/Utility/Math/MathFunc.hpp"

ikk::Camera::Camera(vec3f position, vec3f up, const float yaw, const float pitch) noexcept : m_position(position), m_worldUp(up), m_yaw(yaw), m_pitch(pitch)
{
	this->update();
}

const ikk::mat4x4 ikk::Camera::getViewMatrix() const noexcept
{
	const vec3f f(normalize(vec3f{ this->m_position + this->m_front } - this->m_position));
	const vec3f s(normalize(cross(f, this->m_up)));
	const vec3f u(cross(s, f));

	mat4x4 result{1.f};
	result[0][0] = s.x;
	result[1][0] = s.y;
	result[2][0] = s.z;
	result[0][1] = u.x;
	result[1][1] = u.y;
	result[2][1] = u.z;
	result[0][2] = -f.x;
	result[1][2] = -f.y;
	result[2][2] = -f.z;
	result[3][0] = -dot(s, this->m_position);
	result[3][1] = -dot(u, this->m_position);
	result[3][2] =  dot(f, this->m_position);
    return result;
}

const ikk::mat4x4 ikk::Camera::getProjectionMatrix(const float aspect, const float near, const float far) const noexcept
{
	mat4x4 result{1.f};
	//Ortho
	//result[0][0] = 2.f / (right - left);
	//result[1][1] = 2.f / (top - bottom);
	//result[2][2] = -2.f / (far - near);
	//result[3][0] = -(right + left) / (right - left);
	//result[3][1] = -(top + bottom) / (top - bottom);
	//result[3][2] = -(far + near) / (far - near);
	//Perspective
	const float tanHalfFovy = std::tanf(radian(this->m_zoom) / 2.f);

	result[0][0] = 1.f / (aspect * tanHalfFovy);
	result[1][1] = 1.f / (tanHalfFovy);
	result[2][2] = -(far + near) / (far - near);
	result[2][3] = -1.f;
	result[3][2] = -(2.f * far * near) / (far - near);
	return result;
}

const ikk::mat4x4 ikk::Camera::getProjectionViewMatrix(const float aspect, const float near, const float far) const noexcept
{
    return mat4x4{ this->getViewMatrix() * this->getProjectionMatrix(aspect, near, far) };
}

void ikk::Camera::update() noexcept
{
    vec3f front{};
    front.x = cosf(radian(this->m_yaw)) * cosf(radian(this->m_pitch));
    front.y = sinf(radian(this->m_pitch));
    front.z = sinf(radian(this->m_yaw)) * cosf(radian(this->m_pitch));
    this->m_front = normalize(front);

    this->m_right = normalize(cross(this->m_front, this->m_worldUp));
    this->m_up = normalize(cross(this->m_right, this->m_front));
}