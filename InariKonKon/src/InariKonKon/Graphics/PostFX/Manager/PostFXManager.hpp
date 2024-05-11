#pragma once

#include <memory>
#include <vector>

#include "InariKonKon/Graphics/RenderTexture/RenderTexture.hpp"
#include "InariKonKon/Graphics/PostFX/Effects/PostEffects.hpp"
#include "InariKonKon/Graphics/PostFX/PostFX.hpp"

#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

namespace ikk
{
	class Window;

	namespace priv
	{
		class PostFXManager final : public RenderTexture
		{
		public:
			PostFXManager(const Vector2<std::uint32_t> screenSize, const PostEffects effects = PostEffects::None) noexcept;

			PostFXManager(const PostFXManager&) noexcept = default;
			PostFXManager(PostFXManager&&) noexcept = default;

			PostFXManager& operator=(const PostFXManager&) noexcept = default;
			PostFXManager& operator=(PostFXManager&&) noexcept = default;

			~PostFXManager() noexcept = default;

			[[nodiscard]] const PostEffects getActiveEffetcts() const noexcept;
			void setEffects(const PostEffects newEffect) noexcept;

			void render(const Window& window) const noexcept;
		private:
			PostEffects m_activeEffects;
			std::vector<std::shared_ptr<PostFX>> m_effects;

			[[nodiscard]] void reset() noexcept;
			[[nodiscard]] const bool contains(const PostEffects effect) const noexcept;
		};
	}
}