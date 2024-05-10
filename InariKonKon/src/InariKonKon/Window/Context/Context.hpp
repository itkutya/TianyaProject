#pragma once

#include <unordered_map>
#include <cstdint>
#include <memory>

#include "glad/gl.h"

#include "InariKonKon/Utility/Singleton.hpp"

#define gl ikk::priv::Context::getInstance().getActiveContext()

struct GladGLContext;

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
			Context(Context&&) noexcept = delete;

			Context& operator=(const Context&) noexcept = delete;
			Context& operator=(Context&&) noexcept = delete;

			~Context() noexcept = default;

			void addContext(const Window& window) noexcept;
			void activateContextForWindow(const Window* const window) noexcept;

			[[nodiscard]] const GladGLContext* const getActiveContext() const noexcept;
			[[nodiscard]] GladGLContext* const getActiveContext() noexcept;

			[[nodiscard]] const std::uint32_t& getWindowIDForTheActiveContext() const noexcept;
		private:
			std::unordered_map<std::uint32_t, std::shared_ptr<GladGLContext>> m_context;
			std::shared_ptr<GladGLContext> m_activeContext;
			std::uint32_t m_activeWindowID = 0;
		};
	}
}