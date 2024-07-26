#include "InariKonKon/Input/Keyboard/Keyboard.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "InariKonKon/Window/Window.hpp"

namespace ikk
{
	const bool Keyboard::isKeyDown(Window& window, const KeyCode keycode) noexcept
	{
		return glfwGetKey(window.getUnderlyingWindow(), priv::KeyCodeToGLFWKey(keycode)) == GLFW_PRESS;
	}

	namespace priv
	{
		constexpr int KeyCodeToGLFWKey(const Keyboard::KeyCode key) noexcept
		{
			switch (key)
			{
			case Keyboard::KeyCode::A:
				return GLFW_KEY_A;
			}
			return 0;
		}

		constexpr Keyboard::KeyCode GLFWKeyToKeyCode(const int key) noexcept
		{
			switch (key)
			{
			case GLFW_KEY_A:
				return Keyboard::KeyCode::A;
			}
			return Keyboard::KeyCode::Unknown;
		}
	}
}