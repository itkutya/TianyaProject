#pragma once

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexBufferObject final : public OpenGLObject
		{
		public:
			VertexBufferObject() noexcept;
			~VertexBufferObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;
			void release() noexcept override;
		private:
		};
	}
}