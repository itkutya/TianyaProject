#pragma once

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

			void bind() noexcept override;
			void unbind() noexcept override;
			void release() noexcept override;

			//TODO: TEMP!!!
			unsigned int textureColorbuffer;
			unsigned int rbo;
		private:
		};
	}
}