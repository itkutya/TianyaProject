#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/Vertex/Vertex.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexBufferObject final : public OpenGLObject
		{
		public:
			VertexBufferObject(const std::span<Vertex> vertices, const DrawType type = DrawType::STATIC_DRAW) noexcept;

			VertexBufferObject(const VertexBufferObject&) noexcept = default;
			VertexBufferObject(VertexBufferObject&) noexcept = default;
			VertexBufferObject(VertexBufferObject&&) noexcept = default;

			VertexBufferObject& operator=(const VertexBufferObject&) noexcept = default;
			VertexBufferObject& operator=(VertexBufferObject&) noexcept = default;
			VertexBufferObject& operator=(VertexBufferObject&&) noexcept = default;

			~VertexBufferObject() noexcept;

			void bind() noexcept override;
			void unbind() noexcept override;

			std::span<Vertex> vertices;
			DrawType type;
		private:
		};
	}
}