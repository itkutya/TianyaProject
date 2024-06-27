#pragma once

#include <unordered_map>
#include <cstdint>
#include <memory>

#include "InariKonKon/Utility/Singleton.hpp"

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
			~Context() noexcept = default;

			void activateContextForWindow(const std::uint32_t windowID) noexcept;

			[[nodiscard]] const GladGLContext* const getActiveContext() const noexcept;
			[[nodiscard]] GladGLContext* const getActiveContext() noexcept;

			[[nodiscard]] const std::uint32_t& getWindowIDForTheActiveWindowContext() const noexcept;
		private:
			std::unordered_map<std::uint32_t, std::shared_ptr<GladGLContext>> m_context;
			std::uint32_t m_activeWindowID = 0;

			void addContext(const std::uint32_t windowID) noexcept;
		};
	}
}