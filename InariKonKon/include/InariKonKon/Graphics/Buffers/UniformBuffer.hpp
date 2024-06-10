#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGLObject.hpp"
#include "InariKonKon/Graphics/DrawEnums.hpp"

namespace ikk
{
	namespace priv
	{
		class UniformBuffer final : public OpenGLObject
		{
		public:
			UniformBuffer(const Usage usage = Usage::Static) noexcept;
			~UniformBuffer() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			template<class T, std::size_t N>
			void BufferData(const std::span<T, N> data, const std::uint32_t binding = 0) const noexcept;
		private:
			Usage m_usage;
			
			void BufferDataImpl(const std::size_t size, const void* data, const std::uint32_t binding) const noexcept;
		};

		template<class T, std::size_t N>
		inline void UniformBuffer::BufferData(const std::span<T, N> data, const std::uint32_t binding) const noexcept
		{
			this->BufferDataImpl(sizeof(T) * data.size(), &data[0], binding);
		}
	}
}