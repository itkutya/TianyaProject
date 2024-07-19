#pragma once

#include <vector>

#include "InariKonKon/Utility/Math/Vector2.hpp"

struct GLFWmonitor;

namespace ikk
{
	class Monitor final
	{
	public:
		Monitor(const vec2u size) noexcept;

		Monitor(const Monitor&) noexcept = default;
		Monitor(Monitor&&) noexcept = default;

		Monitor& operator=(const Monitor&) noexcept = default;
		Monitor& operator=(Monitor&&) noexcept = default;

		~Monitor() noexcept = default;

		[[nodiscard]] const GLFWmonitor* getMonitor() const noexcept;
		[[nodiscard]] GLFWmonitor* getMonitor() noexcept;

		[[nodiscard]] const vec2u& getSize() const noexcept;

		[[nodiscard]] static const std::vector<GLFWmonitor*> getAvailableMonitors() noexcept;
	private:
		GLFWmonitor* m_monitor = nullptr;
		const char* m_name = nullptr;
		vec2u m_size = { 0, 0 };
		vec2f m_scale = { 0.f, 0.f };
	};
}