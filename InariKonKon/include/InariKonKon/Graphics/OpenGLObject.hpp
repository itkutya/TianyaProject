#pragma once

#include <cstdint>

namespace ikk
{
	namespace priv
	{
		class OpenGLObject
		{
		public:
			OpenGLObject(const std::uint32_t id = 0) noexcept;

			OpenGLObject(const OpenGLObject& other) noexcept;
			OpenGLObject(OpenGLObject&& other) noexcept;

			virtual OpenGLObject& operator=(const OpenGLObject& other) noexcept final;
			virtual OpenGLObject& operator=(OpenGLObject&& other) noexcept final;

			virtual ~OpenGLObject() noexcept = default;

			virtual void bind() const noexcept = 0;
			virtual void unbind() const noexcept = 0;
			virtual void release() const noexcept = 0;

			virtual const std::uint32_t& getNativeHandle() const noexcept final;
		protected:
			mutable std::uint32_t m_id = 0;
		};
	}
}