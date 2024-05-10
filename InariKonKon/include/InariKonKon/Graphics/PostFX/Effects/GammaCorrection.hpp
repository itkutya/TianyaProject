#pragma once

#include "InariKonKon/Graphics/PostFX/PostFX.hpp"

namespace ikk
{
	class GammaCorrection final : public priv::PostFX
	{
	public:
		GammaCorrection() noexcept;

		GammaCorrection(const GammaCorrection&) noexcept = default;
		GammaCorrection(GammaCorrection&&) noexcept = default;

		GammaCorrection& operator=(const GammaCorrection&) noexcept = default;
		GammaCorrection& operator=(GammaCorrection&&) noexcept = default;

		~GammaCorrection() noexcept = default;

		void apply() noexcept override;
	private:
	};
}