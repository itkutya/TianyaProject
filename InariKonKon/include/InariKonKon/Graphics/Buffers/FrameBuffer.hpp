#pragma once

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	namespace priv
	{
		class FrameBuffer final : public OpenGLObject
		{
		public:
			FrameBuffer() noexcept;
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