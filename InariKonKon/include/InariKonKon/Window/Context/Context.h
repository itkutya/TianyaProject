#pragma once

#include "glad/gl.h"

#include "InariKonKon/Utility/Singleton.hpp"

namespace ikk
{
	class Window;

	namespace priv
	{
		class Context final : public Singleton<Context>
		{
			friend Singleton<Context>;
			Context() noexcept = default;
		public:
			Context(const Context&) noexcept = delete;
			Context(Context&) noexcept = delete;
			Context(Context&&) noexcept = delete;

			Context& operator=(const Context&) noexcept = delete;
			Context& operator=(Context&) noexcept = delete;
			Context& operator=(Context&&) noexcept = delete;

			~Context() noexcept = default;

			[[nodiscard]] const GladGLContext& getContext() const noexcept;
			[[nodiscard]] GladGLContext& getContext() noexcept;
		private:
			GladGLContext m_context{};
		};
	}
}