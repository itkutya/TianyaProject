module;

#include "glad/gl.h"

export module Context;

import <unordered_map>;
import <cstdint>;
import <memory>;
import <cassert>;

import Singleton;

#define gl ikk::priv::Context::getInstance().getActiveContext()

export namespace ikk
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

	void Context::addContext(const std::uint32_t windowID) noexcept
	{
		if (this->m_context.find(windowID) == this->m_context.end())
			this->m_context.emplace(windowID, std::make_shared<GladGLContext>());
	}

	void Context::activateContextForWindow(const std::uint32_t windowID) noexcept
	{
		this->m_activeWindowID = windowID;
	}

	const std::shared_ptr<GladGLContext>& Context::getActiveContext() const noexcept
	{
		assert((this->m_context.find(this->m_activeWindowID) != this->m_context.end()) && "There is no openGL context set!");
		return this->m_context.at(this->m_activeWindowID);
	}

	std::shared_ptr<GladGLContext>& Context::getActiveContext() noexcept
	{
		assert((this->m_context.find(this->m_activeWindowID) != this->m_context.end()) && "There is no openGL context set!");
		return this->m_context.at(this->m_activeWindowID);
	}

	const std::uint32_t& Context::getWindowIDForTheActiveContext() const noexcept
	{
		return this->m_activeWindowID;
	}
}