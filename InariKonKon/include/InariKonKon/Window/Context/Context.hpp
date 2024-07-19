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

			typedef std::uint32_t WindowID;
		public:
			~Context() noexcept = default;

			void activateContextForWindow(const WindowID windowID) noexcept;

			[[nodiscard]] const GladGLContext* const getActiveContext() const noexcept;
			[[nodiscard]] GladGLContext* const getActiveContext() noexcept;

			[[nodiscard]] const WindowID& getActiveWindowContextID() const noexcept;
		private:
			std::unordered_map<WindowID, std::shared_ptr<GladGLContext>> m_context;
			WindowID m_activeWindowID = 0;

			void addContext(const WindowID windowID) noexcept;
		};
	}
}