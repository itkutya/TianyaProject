#pragma once

#include <cstdint>
#include <memory>

namespace ikk
{
	namespace priv
	{
		class OpenGLObject
		{
		public:
			OpenGLObject() noexcept = default;

			OpenGLObject(const OpenGLObject&) noexcept = default;
			OpenGLObject(OpenGLObject&&) noexcept = default;

			virtual OpenGLObject& operator=(const OpenGLObject&) noexcept final = default;
			virtual OpenGLObject& operator=(OpenGLObject&&) noexcept final = default;

			virtual ~OpenGLObject() noexcept = default;

			virtual void bind() const noexcept = 0;
			virtual void unbind() const noexcept = 0;
			virtual void release() const noexcept = 0;

			[[nodiscard]] virtual const std::uint32_t& getNativeHandle() const noexcept final;
		protected:
			[[nodiscard]] virtual const bool canBeDeleted() const noexcept final;

			std::shared_ptr<std::uint32_t> m_id = std::make_shared<std::uint32_t>(0u);
		};
	}
}