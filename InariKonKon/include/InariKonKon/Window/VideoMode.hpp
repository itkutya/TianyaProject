#pragma once

#include <cstdint>

namespace ikk
{
	struct VideoMode final
	{
		VideoMode() noexcept = default;
		VideoMode(const std::uint32_t width, const std::uint32_t height) noexcept;

		VideoMode(const VideoMode&) noexcept = default;
		VideoMode(VideoMode&&) noexcept = default;

		VideoMode& operator=(const VideoMode&) noexcept = default;
		VideoMode& operator=(VideoMode&&) noexcept = default;

		~VideoMode() noexcept = default;

		std::uint32_t width = 0;
		std::uint32_t height = 0;
		//TODO:
		//Monitor support...
	};
}