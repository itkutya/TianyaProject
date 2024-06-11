export module InariKonKon:Color;

import <cstdint>;

export namespace ikk
{
	struct Color final
	{
		constexpr Color() noexcept = default;
		constexpr Color(const float r, const float g, const float b, const float a = 1.f) noexcept
			: r(r), g(g), b(b), a(a) {};
		constexpr Color(const std::uint8_t r, const std::uint8_t g, const std::uint8_t b, const std::uint8_t a = UINT8_MAX) noexcept
			: r(static_cast<float>(r / UINT8_MAX)), g(static_cast<float>(g / UINT8_MAX)), b(static_cast<float>(b / UINT8_MAX)), a(static_cast<float>(a / UINT8_MAX)) {};

		constexpr Color(const Color&) noexcept = default;
		constexpr Color(Color&&) noexcept = default;

		constexpr Color& operator=(const Color&) noexcept = default;
		constexpr Color& operator=(Color&&) noexcept = default;

		constexpr ~Color() noexcept = default;

		float r = 0.f;
		float g = 0.f;
		float b = 0.f;
		float a = 1.f;

		static const Color White;
		static const Color Black;
		static const Color Red;
		static const Color Green;
		static const Color Blue;
		static const Color Yellow;
		static const Color Magenta;
		static const Color Cyan;
		static const Color Transparent;
	};

	inline constexpr Color Color::White(1.f, 1.f, 1.f);
	inline constexpr Color Color::Black(0.f, 0.f, 0.f);
	inline constexpr Color Color::Red(1.f, 0.f, 0.f);
	inline constexpr Color Color::Green(0.f, 1.f, 0.f);
	inline constexpr Color Color::Blue(0.f, 0.f, 1.f);
	inline constexpr Color Color::Yellow(1.f, 1.f, 0.f);
	inline constexpr Color Color::Magenta(1.f, 0.f, 1.f);
	inline constexpr Color Color::Cyan(0.f, 1.f, 1.f);
	inline constexpr Color Color::Transparent(0.f, 0.f, 0.f, 0.f);
}