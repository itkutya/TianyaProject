#pragma once

namespace ikk
{
	class NonCopyable
	{
	public:
		constexpr NonCopyable() noexcept = default;

		constexpr NonCopyable(const NonCopyable&) noexcept = delete;
		constexpr NonCopyable(NonCopyable&&) noexcept = delete;

		virtual constexpr NonCopyable& operator=(const NonCopyable&) noexcept final = delete;
		virtual constexpr NonCopyable& operator=(NonCopyable&&) noexcept final = delete;

		virtual constexpr ~NonCopyable() noexcept = default;
	};
}