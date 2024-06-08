#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/DrawEnums.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	namespace priv
	{
		class ElementBufferObject final : public OpenGLObject
		{
		public:
			ElementBufferObject(const Usage usage = Usage::Static) noexcept;
			~ElementBufferObject() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			const GLType& getType() const noexcept;
		private:
			Usage m_usage;
			GLType m_type = GLType::None;

			template<Number T, std::size_t N>
			void BufferData(const std::span<T, N> indices) noexcept;
			void BufferDataImpl(const std::size_t size, const void* data) const noexcept;

			friend class VertexArrayObject;
		};

		template<Number T, std::size_t N>
		inline void ElementBufferObject::BufferData(const std::span<T, N> indices) noexcept
		{
			if constexpr (std::is_same<T, std::uint8_t>::value)
				this->m_type = GLType::Unsigned_Byte;
			else if constexpr (std::is_same<T, std::uint16_t>::value)
				this->m_type = GLType::Unsigned_Short;
			else if constexpr (std::is_same<T, std::uint32_t>::value)
				this->m_type = GLType::Unsigned_Int;

			this->BufferDataImpl(sizeof(T) * indices.size(), &indices[0]);
		}
	}
}