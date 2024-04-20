#pragma once

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexArrayObject final : public OpenGLObject
		{
		public:
			VertexArrayObject() noexcept;
			~VertexArrayObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;
			void release() noexcept override;
		private:
		};
	}
}