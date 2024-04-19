#pragma once

#include <cstdint>

namespace ikk
{
	namespace priv
	{
		class OpenGLObject
		{
		public:
			OpenGLObject() noexcept = default;

			OpenGLObject(const OpenGLObject&) noexcept = default;
			OpenGLObject(OpenGLObject&) noexcept = default;
			OpenGLObject(OpenGLObject&&) noexcept = default;

			virtual OpenGLObject& operator=(const OpenGLObject&) noexcept = default;
			virtual OpenGLObject& operator=(OpenGLObject&) noexcept = default;
			virtual OpenGLObject& operator=(OpenGLObject&&) noexcept = default;

			virtual ~OpenGLObject() noexcept = default;

			virtual void bind() noexcept = 0;
			virtual void unbind() noexcept = 0;

			virtual const std::uint32_t getNativeHandle() const noexcept final { return this->m_id; };
		protected:
			std::uint32_t m_id = 0;
		};
	}
}