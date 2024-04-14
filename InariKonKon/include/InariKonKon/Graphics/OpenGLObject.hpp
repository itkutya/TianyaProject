#pragma once

#include <cstdint>

namespace ikk
{
	enum class DrawType : std::uint32_t
	{
		STREAM_DRAW = 0x88E0, STATIC_DRAW = 0x88E4, DYNAMIC_DRAW = 0x88E8
	};

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
		protected:
			std::uint32_t m_id = 0;
		};
	}
}