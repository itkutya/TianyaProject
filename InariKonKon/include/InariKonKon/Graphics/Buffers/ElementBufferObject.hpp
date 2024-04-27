#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

namespace ikk
{
	namespace priv
	{
		class ElementBufferObject final : public OpenGLObject
		{
		public:
			ElementBufferObject() noexcept;
			~ElementBufferObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;
			void release() noexcept override;
		private:
		};
	}
}