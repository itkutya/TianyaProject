#pragma once

namespace ikk
{
	class Vertex final
	{
	public:
		constexpr Vertex() noexcept = default;

		constexpr Vertex(const Vertex&) noexcept = default;
		constexpr Vertex(Vertex&) noexcept = default;
		constexpr Vertex(Vertex&&) noexcept = default;

		constexpr Vertex& operator=(const Vertex&) noexcept = default;
		constexpr Vertex& operator=(Vertex&) noexcept = default;
		constexpr Vertex& operator=(Vertex&&) noexcept = default;

		constexpr ~Vertex() noexcept = default;
	private:
	};
}