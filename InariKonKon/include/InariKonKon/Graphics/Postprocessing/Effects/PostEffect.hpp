#pragma once

#include <cstdint>
#include <utility>
#include <bitset>
#include <limits>

namespace ikk
{
	//Order matters when rendering!
	enum class PostEffect : std::uint32_t
	{
		None				= 0 << 0,

		GammaCorrection		= 1 << 0,
		ColorCorrection		= 1 << 1,
		Bloom				= 1 << 2,
		Test				= 1 << 3,

		All = GammaCorrection | ColorCorrection | Bloom | Test
	};

	[[nodiscard]] inline constexpr PostEffect operator| (const PostEffect r, const PostEffect l)
	{
		return static_cast<PostEffect>(std::to_underlying(r) | std::to_underlying(l));
	};

	[[nodiscard]] inline constexpr PostEffect operator& (const PostEffect r, const PostEffect l)
	{
		return static_cast<PostEffect>(std::to_underlying(r) & std::to_underlying(l));
	};

	[[nodiscard]] inline constexpr PostEffect operator^ (const PostEffect r, const PostEffect l)
	{
		return static_cast<PostEffect>(std::to_underlying(r) ^ std::to_underlying(l));
	};

	namespace priv
	{
		inline static constexpr std::size_t PostEffectsCount = 
			std::bitset<std::numeric_limits<decltype(std::to_underlying(PostEffect::All))>::digits>(std::to_underlying(PostEffect::All)).count();
	}
}