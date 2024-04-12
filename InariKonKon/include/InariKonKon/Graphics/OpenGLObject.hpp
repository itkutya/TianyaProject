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
		protected:
			std::uint32_t m_id = 0;
		};
	}
}