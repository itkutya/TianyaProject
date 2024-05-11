#pragma once

#include <cstdint>
#include <utility>
#include <bitset>
#include <limits>

namespace ikk
{
	//Order matters when rendering!
	enum class PostEffects : std::uint32_t
	{
		None				= 0 << 0,

		GammaCorrection		= 1 << 0,
		ColorCorrection		= 1 << 1,
		Bloom				= 1 << 2,
		Test				= 1 << 3,

		All = GammaCorrection | ColorCorrection | Bloom | Test
	};

	[[nodiscard]] inline constexpr PostEffects operator| (const PostEffects l, const PostEffects r)
	{
		return static_cast<PostEffects>(std::to_underlying(l) | std::to_underlying(r));
	};

	[[nodiscard]] inline constexpr PostEffects operator& (const PostEffects l, const PostEffects r)
	{
		return static_cast<PostEffects>(std::to_underlying(l) & std::to_underlying(r));
	};

	namespace priv
	{
		inline static constexpr std::size_t PostEffectsCount = 
			std::bitset<std::numeric_limits<decltype(std::to_underlying(PostEffects::All))>::digits>(std::to_underlying(PostEffects::All)).count();
	}
}