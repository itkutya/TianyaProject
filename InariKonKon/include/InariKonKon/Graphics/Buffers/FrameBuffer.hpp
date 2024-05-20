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

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			//TODO:
			//Resize...

			//TODO: TEMP!!!
			unsigned int textureColorbuffer;
			unsigned int rbo;
		private:
		};
	}
}