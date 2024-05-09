#pragma once

#include <memory>
#include <vector>

#include "InariKonKon/Graphics/PostFX/Effects/PostEffects.hpp"
#include "InariKonKon/Graphics/PostFX/PostFX.hpp"

#include "InariKonKon/Graphics/Buffers/FrameBuffer.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

namespace ikk
{
	class Window;

	namespace priv
	{
		class PostFXManager final
		{
		public:
			PostFXManager(const PostEffects effects = PostEffects::None) noexcept;

			PostFXManager(const PostFXManager&) noexcept = default;
			PostFXManager(PostFXManager&&) noexcept = default;

			PostFXManager& operator=(const PostFXManager&) noexcept = default;
			PostFXManager& operator=(PostFXManager&&) noexcept = default;

			~PostFXManager() noexcept = default;

			[[nodiscard]] const PostEffects getActiveEffetcts() const noexcept;
			void setEffects(const PostEffects newEffect) noexcept;

			void bind() noexcept;
			void unbind() noexcept;
			void render(Window& window) noexcept;
		private:
			PostEffects m_activeEffects;
			std::vector<std::shared_ptr<PostFX>> m_effects;

			//RenderTexture class
			FrameBuffer m_postFXBuffer;
			float quadVertices[24]
			{ // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
				// positions   // texCoords
				-1.0f,  1.0f,  0.0f, 1.0f,
				-1.0f, -1.0f,  0.0f, 0.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,

				-1.0f,  1.0f,  0.0f, 1.0f,
				 1.0f, -1.0f,  1.0f, 0.0f,
				 1.0f,  1.0f,  1.0f, 1.0f
			};
			unsigned int quadVAO, quadVBO;
			//Shader m_shader;
			//RenderState m_state{ &m_shader };
			//

			[[nodiscard]] void reset() noexcept;
			[[nodiscard]] const bool contains(const PostEffects effect) const noexcept;
		};
	}
}