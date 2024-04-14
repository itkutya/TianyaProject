#pragma once

#include <unordered_map>
#include <string_view>
#include <memory>

#include "InariKonKon/Utility/Singleton.hpp"

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
			Context(Context&) noexcept = delete;
			Context(Context&&) noexcept = delete;

			Context& operator=(const Context&) noexcept = delete;
			Context& operator=(Context&) noexcept = delete;
			Context& operator=(Context&&) noexcept = delete;

			~Context() noexcept = default;

			void addContext(const Window* const window) noexcept;
			void activateContextForWindow(const Window* const window) noexcept;

			[[nodiscard]] const GladGLContext* const getActiveContext() const noexcept;
			[[nodiscard]] GladGLContext* const getActiveContext() noexcept;
		private:
			std::unordered_map<std::string_view, std::shared_ptr<GladGLContext>> m_context;
			std::shared_ptr<GladGLContext> m_activeContext;
		};

		inline static GladGLContext* const gl() noexcept
		{
			return Context::getInstance().getActiveContext();
		}
	}
}