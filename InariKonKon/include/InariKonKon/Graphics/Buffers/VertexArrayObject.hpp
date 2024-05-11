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

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;
		private:
		};
	}
}