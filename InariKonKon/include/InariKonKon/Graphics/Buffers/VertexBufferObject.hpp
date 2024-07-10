#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexBufferObject final : public OpenGLObject
		{
		public:
			VertexBufferObject(const std::uint32_t usage = GL_STATIC_DRAW) noexcept;
			~VertexBufferObject() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			template<VertexType T, std::size_t N>
			void BufferData(const std::span<T, N> vertices) const noexcept;
		private:
			std::uint32_t m_usage;
		};

		template<VertexType T, std::size_t N>
		void VertexBufferObject::BufferData(const std::span<T, N> vertices) const noexcept
		{
			this->bind();
			gl->BufferData(GL_ARRAY_BUFFER, sizeof(T) * vertices.size(), &vertices[0], this->m_usage);
			//this->unbind();
		}
	}
}