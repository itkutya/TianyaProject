#pragma once

#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Postprocessing/Effects/PostEffect.hpp"

namespace ikk
{
	class Window;

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

		void apply(const Window& window) const noexcept;
	private:
		PostEffect m_activeEffects;
		Shader m_postprocessing;

		[[nodiscard]] const Shader reset() noexcept;
		[[nodiscard]] const bool contains(const PostEffect effect) const noexcept;
	};
}