#pragma once

#include <vector>

#include "InariKonKon/Graphics/Postprocessing/Effects/PostEffect.hpp"
#include "InariKonKon/Graphics/Postprocessing/Effects/PostFX.hpp"

namespace ikk
{
	class Window;
	namespace priv
	{
		class Postprocesser
		{
		public:
			Postprocesser(const PostEffect effects = PostEffect::None) noexcept;

			Postprocesser(const Postprocesser&) noexcept = default;
			Postprocesser(Postprocesser&&) noexcept = default;

			Postprocesser& operator=(const Postprocesser&) noexcept = default;
			Postprocesser& operator=(Postprocesser&&) noexcept = default;

			~Postprocesser() noexcept = default;

			[[nodiscard]] const PostEffect getActiveEffetcts() const noexcept;
			void setEffects(const PostEffect newEffect) noexcept;

			void begin(const Window& window) noexcept;
			void end(const Window& window) noexcept;
		private:
			PostEffect m_activeEffects;
			std::vector<PostFX*> m_effects;

			[[nodiscard]] void reset() noexcept;
			[[nodiscard]] const bool contains(const PostEffect effect) const noexcept;
		};
	}
}