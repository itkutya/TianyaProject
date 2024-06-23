module;

#include "glad/gl.h"

export module Context;

import <unordered_map>;
import <cstdint>;
import <memory>;

import Singleton;

export namespace ikk
{
	export namespace priv
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

			[[nodiscard]] const GladGLContext* const getActiveContext() const noexcept;
			[[nodiscard]] GladGLContext* const getActiveContext() noexcept;

			[[nodiscard]] const std::uint32_t& getWindowIDForTheActiveContext() const noexcept;
		private:
			std::unordered_map<std::uint32_t, std::shared_ptr<GladGLContext>> m_context;
			std::uint32_t m_activeWindowID = 0;
		};

		void Context::addContext(const std::uint32_t windowID) noexcept
		{
			if (this->m_context.find(windowID) == this->m_context.end())
				this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
		}

		void Context::activateContextForWindow(const std::uint32_t windowID) noexcept
		{
			if (this->m_context.find(windowID) == this->m_context.end())
				this->addContext(windowID);
			this->m_activeWindowID = windowID;
		}

		const GladGLContext* const Context::getActiveContext() const noexcept
		{
			if (this->m_context.find(this->m_activeWindowID) == this->m_context.end())
				return nullptr;
			return this->m_context.at(this->m_activeWindowID).get();
		}

		GladGLContext* const Context::getActiveContext() noexcept
		{
			if (this->m_context.find(this->m_activeWindowID) == this->m_context.end())
				return nullptr;
			return this->m_context.at(this->m_activeWindowID).get();
		}

		const std::uint32_t& Context::getWindowIDForTheActiveContext() const noexcept
		{
			return this->m_activeWindowID;
		}
	}
}