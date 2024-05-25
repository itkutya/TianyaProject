#pragma once

#include <span>

#include "InariKonKon/Graphics/Vertex/Vertex.hpp"
#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/DrawEnums.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	namespace priv
	{
		class VertexBufferObject final : public OpenGLObject
		{
		public:
			VertexBufferObject(const Draw::Usage usage = Draw::Usage::Static) noexcept;
			~VertexBufferObject() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			template<class T, std::size_t N>
			void BufferData(const std::span<T, N> vertices) noexcept;
		private:
			Draw::Usage m_usage;
			void BufferDataImpl(const std::size_t size, const void* data) const noexcept;
		};

		template<class T, std::size_t N>
		inline void VertexBufferObject::BufferData(const std::span<T, N> vertices) noexcept
		{
			this->BufferDataImpl(sizeof(T) * vertices.size(), &vertices[0]);
		}
	}
}