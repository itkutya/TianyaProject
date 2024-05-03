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

	[[nodiscard]] inline constexpr PostEffects operator| (const PostEffects r, const PostEffects l)
	{
		return static_cast<PostEffects>(std::to_underlying(r) | std::to_underlying(l));
	};

	[[nodiscard]] inline constexpr PostEffects operator& (const PostEffects r, const PostEffects l)
	{
		return static_cast<PostEffects>(std::to_underlying(r) & std::to_underlying(l));
	};

	namespace priv
	{
		inline static constexpr std::size_t PostEffectsCount = 
			std::bitset<std::numeric_limits<decltype(std::to_underlying(PostEffects::All))>::digits>(std::to_underlying(PostEffects::All)).count();
	}
}