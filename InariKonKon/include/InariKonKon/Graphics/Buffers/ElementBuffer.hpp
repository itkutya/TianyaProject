#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	namespace priv
	{
		class ElementBufferObject final : public OpenGLObject
		{
		public:
			ElementBufferObject(const std::uint32_t usage = GL_STATIC_DRAW) noexcept;
			~ElementBufferObject() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			template<Number T, std::size_t N>
			void BufferData(const std::span<T, N> indices) noexcept;

			const std::uint32_t& getType() const noexcept;
		private:
			std::uint32_t m_usage;
			std::uint32_t m_type = GL_NONE;
		};

		template<Number T, std::size_t N>
		void ElementBufferObject::BufferData(const std::span<T, N> indices) noexcept
		{
			if constexpr (std::is_same<T, std::uint8_t>::value)
				this->m_type = GL_UNSIGNED_BYTE;
			else if constexpr (std::is_same<T, std::uint16_t>::value)
				this->m_type = GL_UNSIGNED_SHORT;
			else if constexpr (std::is_same<T, std::uint32_t>::value)
				this->m_type = GL_UNSIGNED_INT;

			if (this->m_id == 0)
				gl->GenBuffers(1, &this->m_id);
			this->bind();
			gl->BufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T) * indices.size(), &indices[0], this->m_usage);
			this->unbind();
		}
	}
}