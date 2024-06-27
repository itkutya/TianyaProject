#pragma once

#include <span>

#include "InariKonKon/Graphics/Buffers/VertexBufferObject.hpp"
#include "InariKonKon/Graphics/Buffers/ElementBuffer.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

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

			template<VertexType VT, std::size_t VN, Number IT, std::size_t IN>
			void setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices, ElementBufferObject& ebo, const std::span<IT, IN> indices) const noexcept;
			template<VertexType VT, std::size_t VN>
			void setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices) const noexcept;
		private:
			void setupVertexAttributes() const noexcept;
		};

		template<VertexType VT, std::size_t VN, Number IT, std::size_t IN>
		void VertexArrayObject::setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices, ElementBufferObject& ebo, const std::span<IT, IN> indices) const noexcept
		{
			this->bind();
			vbo.BufferData(vertices);
			ebo.BufferData(indices);
			this->setupVertexAttributes();
			this->unbind();
		}

		template<VertexType VT, std::size_t VN>
		void VertexArrayObject::setup(VertexBufferObject& vbo, const std::span<VT, VN> vertices) const noexcept
		{
			this->bind();
			vbo.BufferData(vertices);
			this->setupVertexAttributes();
			this->unbind();
		}
	}
}