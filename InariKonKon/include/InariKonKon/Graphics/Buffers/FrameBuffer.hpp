#pragma once

#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"

namespace ikk
{
	namespace priv
	{
		class FrameBuffer final : public priv::OpenGLObject
		{
		public:
			FrameBuffer(const vec2u screenSize) noexcept;
			~FrameBuffer() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			void resize(const vec2u newSize) noexcept;

			const Texture& getTexture() const noexcept;
			Texture& getTexture() noexcept;
		private:
			Texture m_texture;
			unsigned int rbo;
		};
	}
}