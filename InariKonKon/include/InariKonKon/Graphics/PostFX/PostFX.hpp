#pragma once

#include <memory>

#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/PostFX/PostEffects.hpp"
#include "InariKonKon/Graphics/Shader/Shader.hpp"
#include "InariKonKon/Graphics/Camera/Camera.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

namespace ikk
{
	class Window;

	namespace priv
	{
		class PostFX final
		{
		public:
			PostFX(const vec2u screenSize, const PostEffects effects = PostEffects::None) noexcept;

			PostFX(const PostFX&) noexcept = default;
			PostFX(PostFX&&) noexcept = default;

			PostFX& operator=(const PostFX&) noexcept = default;
			PostFX& operator=(PostFX&&) noexcept = default;

			~PostFX() noexcept = default;

			[[nodiscard]] const FrameBuffer& getFrameBuffer() const noexcept;
			[[nodiscard]] FrameBuffer& getFrameBuffer() noexcept;

			[[nodiscard]] const PostEffects getActiveEffetcts() const noexcept;
			void setEffects(const PostEffects newEffect) noexcept;

			void clear() const noexcept;
			void activate() const noexcept;
			void display(const Window& window) const noexcept;
		private:
			PostEffects m_activeEffects;
			std::shared_ptr<Shader> m_effects;

			FrameBuffer m_frameBuffer;
			Quad<Dimension::_2D> m_quadScreen;
			Camera<Projection::Ortho> m_cameraScreen;

			[[nodiscard]] void reset() noexcept;
			[[nodiscard]] const bool contains(const PostEffects effect) const noexcept;

			void setDefaultFrameBuffer() const noexcept;
		};
	}
}