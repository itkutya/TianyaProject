module;

#include "InariKonKon/Graphics/OpenGL.hpp"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

export module Window;

import <exception>;
import <string>;
import <print>;
/*
#include "InariKonKon/Utility/Math/Vector2.hpp"
#include "InariKonKon/Graphics/Drawable.hpp"
*/

export import VideoMode;
export import Color;

import EventManager;
import Context;

inline static std::uint32_t s_uniqueID = 0;

static void glfwError(int id, const char* description) noexcept
{
	std::print("{}: {}\n", id, description);
}

export namespace ikk
{
	class Window final
	{
	public:
		struct Settings
		{
			VideoMode videomode;
			std::uint32_t fpslimit = 0;
			bool vsync = true;
			bool fullscreem = false;
		};

		Window(const std::u8string& title, const Window::Settings settings);

		Window(const Window&) noexcept = default;
		Window(Window&&) noexcept = default;

		Window& operator=(const Window&) noexcept = default;
		Window& operator=(Window&&) noexcept = default;

		~Window() noexcept;

		[[nodiscard]] const bool shouldClose() const noexcept;

		void setActive(const bool active = true) const noexcept;

		void handleEvents() const noexcept;
		void clear(const Color clearColor) const noexcept;
		void render() const noexcept;
		/*
		[[nodiscard]] const std::uint32_t getFPSLimit() const noexcept;
		void setFPSLimit(const std::uint32_t limit) noexcept;

		[[nodiscard]] const bool isVSyncEnabled() const noexcept;
		void setVSync(const bool vsync) noexcept;

		[[nodiscard]] const std::string& getTitle() const noexcept;
		void setTitle(const std::string& title) noexcept;

		[[nodiscard]] const Vector2<std::uint32_t> getSize() const noexcept;
		void setSize(const Vector2<std::uint32_t> size) noexcept;

		[[nodiscard]] const float getAspectRatio() const noexcept;

		template<Dimension D, Projection P>
		void draw(const Drawable<D>& drawable, RenderState<D, P>& state = {}) const noexcept;

		void draw(const Primitive type, const std::size_t count, const int offset = 0) const noexcept;
		void draw(const Primitive type, const std::size_t indiciesCount, const GLType eboType) const noexcept;
		*/
	private:
		std::uint32_t m_id;
		std::u8string m_title;
		Window::Settings m_settings;
		GLFWwindow* m_window;

		EventManager m_eventManager{};

		GLFWwindow* const create(const std::u8string& title, const VideoMode vm) const noexcept;
		void initWindowEvents() noexcept;

		friend class Application;
		[[nodiscard]] const std::queue<Event>& getEventQueue() const noexcept;
		[[nodiscard]] std::queue<Event>& getEventQueue() noexcept;
	};

	Window::Window(const std::u8string& title, const Window::Settings settings)
		try : m_id(++s_uniqueID), m_title(title), m_settings(settings), m_window(create(title, settings.videomode))
	{
		if (this->m_window == nullptr)
			throw std::exception("Cannot create window.");

		glfwMakeContextCurrent(this->m_window);
		Context::getInstance().addContext(this->m_id);
		this->setActive();

		if (!gladLoadGLContext(Context::getInstance().getActiveContext(), glfwGetProcAddress))
			throw std::exception("Error cannot load openGL.");

		gl->Viewport(0, 0, settings.videomode.width, settings.videomode.height);

		//this->setFPSLimit(settings.fpslimit);
		//this->setVSync(settings.vsync);
		this->initWindowEvents();
	}
	catch (const std::exception& e)
	{
		//Error is visual only...
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
			if (Context::getInstance().getWindowIDForTheActiveContext() != this->m_id)
			{
				glfwMakeContextCurrent(this->m_window);
				Context::getInstance().activateContextForWindow(this->m_id);
			}
		}
		else
		{
			Context::getInstance().activateContextForWindow(0);
			glfwMakeContextCurrent(nullptr);
		}
	}

	void Window::handleEvents() const noexcept
	{
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

	GLFWwindow* const Window::create(const std::u8string& title, const VideoMode vm) const noexcept
	{
		glfwSetErrorCallback(&glfwError);
		if (!glfwInit())
			return nullptr;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		return glfwCreateWindow(vm.width, vm.height, reinterpret_cast<const char*>(title.c_str()), NULL, NULL);
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