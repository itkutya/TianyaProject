#include "InariKonKon/Window/Monitor.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

namespace ikk
{
	Monitor::Monitor(const vec2u size) noexcept : m_size(size)
	{
		this->m_monitor = glfwGetPrimaryMonitor();
		if (this->m_monitor != nullptr)
		{
			this->m_name = glfwGetMonitorName(this->m_monitor);

			if (size.x == 0 || size.y == 0)
			{
				const auto vm = glfwGetVideoMode(this->m_monitor);
				this->m_size = { static_cast<std::uint32_t>(vm->width), static_cast<std::uint32_t>(vm->height) };
			}
			glfwGetMonitorContentScale(this->m_monitor, &this->m_scale.x, &this->m_scale.y);
		}
	}

	const GLFWmonitor* Monitor::getMonitor() const noexcept
	{
		return this->m_monitor;
	}

	GLFWmonitor* Monitor::getMonitor() noexcept
	{
		return this->m_monitor;
	}

	const vec2u& Monitor::getSize() const noexcept
	{
		return this->m_size;
	}

	const std::vector<GLFWmonitor*> Monitor::getAvailableMonitors() noexcept
	{
		int count = 0;
		GLFWmonitor** monitors = glfwGetMonitors(&count);

		static std::vector<GLFWmonitor*> temp{};
		temp.clear();

		for (std::size_t i = 0; i < count; ++i)
			temp.emplace_back(monitors[i]);

		return temp;
	}
}