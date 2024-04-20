#pragma once

#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Utility/Math/Vector3.hpp"
#include "InariKonKon/Utility/Color.hpp"

namespace ikk
{
	struct Vertex final
	{
		constexpr Vertex() noexcept = default;
		constexpr Vertex(const Vector3<float> position, const Color color = { 1.f, 1.f, 1.f, 1.f }, const Vector2<float> texCoord = { 0.f, 0.f }) noexcept 
			: position(position), color(color), texCoord(texCoord) {};

		constexpr Vertex(const Vertex&) noexcept = default;
		constexpr Vertex(Vertex&&) noexcept = default;

		constexpr Vertex& operator=(const Vertex&) noexcept = default;
		constexpr Vertex& operator=(Vertex&&) noexcept = default;

		constexpr ~Vertex() noexcept = default;

		Vector3<float> position;
		Color color;
		Vector2<float> texCoord;
	};
}