#pragma once

#include <cstdint>

namespace ikk
{
	enum class PostEffect : std::uint32_t
	{
		None				= 0 << 0,
		GammaCorrection		= 1 << 0,
		ColourCorrection	= 1 << 1,
		Bloom				= 1 << 2,

		All = GammaCorrection | ColourCorrection
	};

	[[nodiscard]] inline constexpr PostEffect operator~ (const PostEffect r)
	{
		return static_cast<PostEffect>(~static_cast<std::uint32_t>(r));
	};

	[[nodiscard]] inline constexpr PostEffect operator| (const PostEffect r, const PostEffect l)
	{
		return static_cast<PostEffect>(static_cast<std::uint32_t>(r) | static_cast<std::uint32_t>(l));
	};

	[[nodiscard]] inline constexpr PostEffect operator& (const PostEffect r, const PostEffect l)
	{
		return static_cast<PostEffect>(static_cast<std::uint32_t>(r) & static_cast<std::uint32_t>(l));
	};

	[[nodiscard]] inline constexpr PostEffect operator^ (const PostEffect r, const PostEffect l)
	{
		return static_cast<PostEffect>(static_cast<std::uint32_t>(r) ^ static_cast<std::uint32_t>(l));
	};
}