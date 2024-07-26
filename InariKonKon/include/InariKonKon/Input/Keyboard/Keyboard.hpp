#pragma once

namespace ikk
{
	class Window;

	class Keyboard
	{
	public:
		enum class KeyCode
		{
			Unknown = 0, A
		};

		enum class ScanCode
		{
			Unknown = 0, A
		};

		static const bool isKeyDown(Window& window, const KeyCode keycode) noexcept;
	private:
	};

	namespace priv
	{
		static constexpr int KeyCodeToGLFWKey(const Keyboard::KeyCode key) noexcept;
		static constexpr Keyboard::KeyCode GLFWKeyToKeyCode(const int key) noexcept;
	}
}