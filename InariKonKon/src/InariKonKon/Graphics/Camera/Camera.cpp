#include "InariKonKon/Graphics/Camera/Camera.hpp"

#include "InariKonKon/Utility/Math/MathFunc.hpp"

ikk::Camera::Camera(const vec3f position, const vec3f worldUp, const float yaw, const float pitch) noexcept : m_position(position), m_worldUp(worldUp), m_yaw(yaw), m_pitch(pitch)
{
	this->updateVectors();
}

const ikk::mat4x4 ikk::Camera::getViewMatrix() const noexcept
{
	const vec3f dir{ normalize(vec3f{ this->m_position + this->m_direction } - this->m_position) };
	const vec3f up{ normalize(cross(dir, this->m_up)) };
	const vec3f right{ cross(up, dir) };

	mat4x4 result{ 1.f };

	result[0][0] = right.x;
	result[1][0] = right.y;
	result[2][0] = right.z;
	result[3][0] = -dot(right, this->m_position);

	result[0][1] = up.x;
	result[1][1] = up.y;	
	result[2][1] = up.z;
	result[3][1] = -dot(up, this->m_position);

	result[0][2] = -dir.x;
	result[1][2] = -dir.y;
	result[2][2] = -dir.z;
	result[3][2] =  dot(dir, this->m_position);

    return result;
}

const ikk::mat4x4 ikk::Camera::getProjectionMatrix(const float aspect, const float near, const float far) const noexcept
{
	mat4x4 result{ 0.f };
	//Ortho
	//result[0][0] = 2.f / (right - left);
	//result[1][1] = 2.f / (top - bottom);
	//result[2][2] = -2.f / (far - near);
	//result[3][0] = -(right + left) / (right - left);
	//result[3][1] = -(top + bottom) / (top - bottom);
	//result[3][2] = -(far + near) / (far - near);
	//Perspective
	const float tanHalfFov = std::tanf(radian(this->m_FOV) / 2.f);

	result[0][0] = 1.f / (aspect * tanHalfFov);

	result[1][1] = 1.f / tanHalfFov;

	result[2][2] = -(far + near) / (far - near);
	result[2][3] = -1.f;

	result[3][2] = -(2.f * far * near) / (far - near);

	return result;
}

const ikk::mat4x4 ikk::Camera::getProjectionViewMatrix(const float aspect, const float near, const float far) const noexcept
{
    return mat4x4{ this->getViewMatrix() * this->getProjectionMatrix(aspect, near, far) };
}

#include "glfw/glfw3.h"
#include "InariKonKon/Window/Window.hpp"

void ikk::Camera::update(const Window& window, const Time& dt) noexcept
{
	if (glfwGetKey(window.m_window, GLFW_KEY_W) == GLFW_PRESS)
		this->m_position += this->m_direction * this->m_speed * dt.asSeconds();
	if (glfwGetKey(window.m_window, GLFW_KEY_S) == GLFW_PRESS)
		this->m_position -= this->m_direction * this->m_speed * dt.asSeconds();
	if (glfwGetKey(window.m_window, GLFW_KEY_A) == GLFW_PRESS)
		this->m_position -= normalize(cross(this->m_direction, this->m_up)) * this->m_speed * dt.asSeconds();
	if (glfwGetKey(window.m_window, GLFW_KEY_D) == GLFW_PRESS)
		this->m_position += normalize(cross(this->m_direction, this->m_up)) * this->m_speed * dt.asSeconds();

	this->updateVectors();
}

void ikk::Camera::updateVectors() noexcept
{
    vec3f dir{};
    dir.x = cos(radian(this->m_yaw)) * cos(radian(this->m_pitch));
    dir.y = sin(radian(this->m_pitch));
    dir.z = sin(radian(this->m_yaw)) * cos(radian(this->m_pitch));
    this->m_direction = normalize(dir);

    this->m_right = normalize(cross(this->m_direction, this->m_worldUp));
    this->m_up = normalize(cross(this->m_right, this->m_direction));
}