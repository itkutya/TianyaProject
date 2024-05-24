#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/DrawOptions.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	namespace priv
	{
		class ElementBufferObject final : public OpenGLObject
		{
		public:
			ElementBufferObject(const Draw::Usage usage = Draw::Usage::STATIC_DRAW) noexcept;
			~ElementBufferObject() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			template<Number T, std::size_t N>
			void BufferData(const std::span<T, N> indices) noexcept;

			const GLType& getType() const noexcept;
		private:
			Draw::Usage m_usage;
			GLType m_type = GLType::NONE;

			void BufferDataImpl(const std::size_t size, const void* data) const noexcept;
		};

		template<Number T, std::size_t N>
		inline void ElementBufferObject::BufferData(const std::span<T, N> indices) noexcept
		{
			if constexpr (std::is_same<T, std::uint8_t>::value)
				this->m_type = GLType::UNSIGNED_BYTE;
			else if constexpr (std::is_same<T, std::uint16_t>::value)
				this->m_type = GLType::UNSIGNED_SHORT;
			else if constexpr (std::is_same<T, std::uint32_t>::value)
				this->m_type = GLType::UNSIGNED_INT;

			this->BufferDataImpl(sizeof(T) * indices.size(), &indices[0]);
		}
	}
}