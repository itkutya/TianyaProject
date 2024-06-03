#pragma once

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Utility/Math/Vector2.hpp"

namespace ikk
{
	namespace priv
	{
		class FrameBuffer final : public OpenGLObject
		{
		public:
			FrameBuffer(const Vector2<std::uint32_t> screenSize) noexcept;
			~FrameBuffer() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			//TODO:
			//void resize(const Vector2<std::uint32_t> size) noexcept;

			const Texture& getTexture() const noexcept;
			Texture& getTexture() noexcept;
		private:
			Texture m_texture;
			unsigned int rbo;
		};
	}
}