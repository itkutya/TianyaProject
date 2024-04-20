#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexBufferObject final : public OpenGLObject
		{
		public:
			VertexBufferObject(const std::span<Vertex> vertices, const Drawable::Type type = Drawable::Type::STATIC_DRAW) noexcept;
			~VertexBufferObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;
			void release() noexcept override;

			std::span<Vertex> vertices;
			Drawable::Type type;
		private:
		};
	}
}