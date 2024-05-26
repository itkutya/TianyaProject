#pragma once

#include <unordered_map>
#include <cstdint>
#include <memory>

#include "InariKonKon/Utility/Singleton.hpp"

#define gl ikk::priv::Context::getInstance().getActiveContext()

struct GladGLContext;

namespace ikk
{
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

			void addContext(const std::uint32_t windowID) noexcept;
			void activateContextForWindow(const std::uint32_t windowID) noexcept;

			[[nodiscard]] const std::shared_ptr<GladGLContext>& getActiveContext() const noexcept;
			[[nodiscard]] std::shared_ptr<GladGLContext>& getActiveContext() noexcept;

			[[nodiscard]] const std::uint32_t& getWindowIDForTheActiveContext() const noexcept;
		private:
			std::unordered_map<std::uint32_t, std::shared_ptr<GladGLContext>> m_context;
			std::uint32_t m_activeWindowID = 0;
		};
	}
}