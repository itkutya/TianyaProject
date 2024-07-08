#pragma once

#include <span>

#include "InariKonKon/Graphics/OpenGL/OpenGLObject.hpp"
#include "InariKonKon/Graphics/OpenGL/OpenGL.hpp"
#include "InariKonKon/Utility/TypeDefs.hpp"

namespace ikk
{
	namespace priv
	{
		//TODO:
		//Look into this a bit more...
		class UniformBuffer final : public OpenGLObject
		{
		public:
			UniformBuffer(const std::uint32_t usage = GL_STATIC_DRAW) noexcept;
			~UniformBuffer() noexcept;

			void bind() const noexcept override;
			void unbind() const noexcept override;
			void release() const noexcept override;

			template<class T, std::size_t N>
			void BufferData(const std::span<T, N> data, const std::uint32_t binding = 0) const noexcept;
		private:
			std::uint32_t m_usage;
		};

		template<class T, std::size_t N>
		void UniformBuffer::BufferData(const std::span<T, N> data, const std::uint32_t binding) const noexcept
		{
			if (this->m_id == 0)
				gl->GenBuffers(1, &this->m_id);
			this->bind();
			gl->BindBufferBase(GL_UNIFORM_BUFFER, binding, this->m_id);
			gl->BufferData(GL_UNIFORM_BUFFER, sizeof(T) * data.size(), &data[0], this->m_usage);
			this->unbind();
		}
	}
}