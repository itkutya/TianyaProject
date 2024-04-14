#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexArrayObject final : public OpenGLObject
		{
		public:
			VertexArrayObject() noexcept;

			VertexArrayObject(const VertexArrayObject&) noexcept = default;
			VertexArrayObject(VertexArrayObject&) noexcept = default;
			VertexArrayObject(VertexArrayObject&&) noexcept = default;

			VertexArrayObject& operator=(const VertexArrayObject&) noexcept = default;
			VertexArrayObject& operator=(VertexArrayObject&) noexcept = default;
			VertexArrayObject& operator=(VertexArrayObject&&) noexcept = default;

			~VertexArrayObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;
		private:
		};
	}
}