#include "InariKonKon/Window/Window.hpp"

#include <exception>
#include <print>

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

inline static std::uint32_t s_uniqueID = 0;

static void glfwError(int id, const char* description) noexcept
{
	std::print("{}: {}\n", id, description);
}

namespace ikk
{
	Window::Window(const std::u8string& title, const Window::Settings settings)
	try : m_id(++s_uniqueID), m_title(title), m_settings(settings), m_window(create(title, settings.monitor))
	{
		if (this->m_window == nullptr)
			throw std::exception("Cannot create window.");

		glfwMakeContextCurrent(this->m_window);
		priv::Context::getInstance().activateContextForWindow(this->m_id);
		this->setActive();

		if (!gladLoadGLContext(priv::Context::getInstance().getActiveContext(), glfwGetProcAddress))
			throw std::exception("Error cannot load openGL.");

		gl->Viewport(0, 0, settings.monitor.size.x, settings.monitor.size.y);

		this->setFPSLimit(settings.fpslimit);
		this->setVSync(settings.vsync);
		this->initWindowEvents();
	}
	catch (const std::exception& e)
	{
		std::print("Exception was thrown while creating window.\nERROR: {}", e.what());
		throw e;
	}

	Window::~Window() noexcept
	{
		glfwTerminate();
	}

	const bool Window::shouldClose() const noexcept
	{
		return glfwWindowShouldClose(this->m_window);
	}

	void Window::setActive(const bool active) const noexcept
	{
		if (active)
		{
			if (priv::Context::getInstance().getWindowIDForTheActiveWindowContext() != this->m_id)
			{
				glfwMakeContextCurrent(this->m_window);
				priv::Context::getInstance().activateContextForWindow(this->m_id);
			}
		}
		else
		{
			priv::Context::getInstance().activateContextForWindow(0);
			glfwMakeContextCurrent(nullptr);
		}
	}

	void Window::handleEvents() const noexcept
	{
		this->setActive();
		glfwPollEvents();
	}

	void Window::clear(const Color clearColor) const noexcept
	{
		this->setActive();
		gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
		gl->ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void Window::render() const noexcept
	{
		this->setActive();
		glfwSwapBuffers(this->m_window);
	}

	const std::uint32_t& Window::getFPSLimit() const noexcept
	{
		return this->m_settings.fpslimit;
	}

	void Window::setFPSLimit(const std::uint32_t limit) noexcept
	{
		this->m_settings.fpslimit = limit;
		this->m_settings.vsync = (limit != 0) ? false : this->m_settings.vsync;
		glfwSwapInterval(this->m_settings.vsync);
	}

	const bool& Window::isVSyncEnabled() const noexcept
	{
		return this->m_settings.vsync;
	}

	void Window::setVSync(const bool vsync) noexcept
	{
		this->m_settings.fpslimit = (vsync == true) ? 0 : this->m_settings.fpslimit;
		this->m_settings.vsync = vsync;
		glfwSwapInterval(this->m_settings.vsync);
	}

	const std::u8string& Window::getTitle() const noexcept
	{
		return this->m_title;
	}

	void Window::setTitle(const std::u8string& title) noexcept
	{
		this->m_title = title;
		glfwSetWindowTitle(this->m_window, reinterpret_cast<const char*>(title.c_str()));
	}

	const float Window::getAspectRatio() const noexcept
	{
		return static_cast<float>(this->getSize().x) / static_cast<float>(this->getSize().y);
	}

	const vec2u& Window::getSize() const noexcept
	{
		return this->m_settings.monitor.size;
	}

	void Window::setSize(const vec2u size) noexcept
	{
		glfwSetWindowSize(this->m_window, static_cast<int>(size.x), static_cast<int>(size.y));
	}

	GLFWwindow* const Window::create(const std::u8string& title, const Monitor vm) const noexcept
	{
		glfwSetErrorCallback(&glfwError);

		if (!glfwInit())
			return nullptr;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return glfwCreateWindow(static_cast<int>(vm.size.x), static_cast<int>(vm.size.y), reinterpret_cast<const char*>(title.c_str()), NULL, NULL);
	}

	void Window::initWindowEvents() noexcept
	{
		glfwSetWindowUserPointer(this->m_window, reinterpret_cast<void*>(this));

		static auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
			{
				Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
				handler->setActive();
				gl->Viewport(0, 0, width, height);
				handler->getEventQueue().emplace(Event::Type::FrameBufferResized, Event::SizeEvent{ static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) });
			};
		glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
		//TODO:
		//Impl rest of them...
	}

	const std::queue<Event>& Window::getEventQueue() const noexcept
	{
		return this->m_eventManager.getEventQueue();
	}

	std::queue<Event>& Window::getEventQueue() noexcept
	{
		return this->m_eventManager.getEventQueue();
	}
}