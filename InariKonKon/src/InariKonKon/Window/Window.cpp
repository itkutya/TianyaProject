#include "InariKonKon/Window/Window.hpp"

#include "glad/gl.h"
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

ikk::Window::Window(const std::string_view title, const VideoMode vm, const Window::Settings settings)
try : m_title(title), m_settings(settings), m_window(create(title, vm)), m_context(new GladGLContext())
{
    if (this->m_window == nullptr)
        throw std::exception("Cannot create window.");

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLContext(this->m_context, glfwGetProcAddress))
        throw std::exception("Error cannot load openGL.");

    this->m_context->Viewport(0, 0, vm.width, vm.height);
    
    glfwSwapInterval(this->m_settings.vsync);
    this->initWindowEvents();
}
catch (const std::exception& e)
{
	std::print("Exception was thrown while creating window.\nERROR: {}", e.what());
	throw e;
}

ikk::Window::~Window() noexcept
{
	glfwTerminate();
    if (this->m_context != nullptr)
        delete this->m_context;
    this->m_context = nullptr;
}

const bool ikk::Window::shouldClose() const noexcept
{
	return glfwWindowShouldClose(this->m_window);
}

void ikk::Window::handleEvents() noexcept
{
    glfwPollEvents();
}

void ikk::Window::clear(const Color clearColor) noexcept
{
    this->m_context->ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    this->m_context->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ikk::Window::render() noexcept
{
    glfwSwapBuffers(this->m_window);
}

const std::uint32_t& ikk::Window::getFPSLimit() const noexcept
{
    return this->m_settings.fpslimit;
}

void ikk::Window::setFPSLimit(const std::uint32_t limit) noexcept
{
    this->m_settings.fpslimit = limit;
    this->m_settings.vsync = (limit != 0) ? false : this->m_settings.vsync;
    glfwSwapInterval(this->m_settings.vsync);
}

const bool ikk::Window::isVSyncEnabled() const noexcept
{
    return this->m_settings.vsync;
}

void ikk::Window::setVSync(const bool vsync) noexcept
{
    this->m_settings.fpslimit = (vsync == true) ? 0 : this->m_settings.fpslimit;
    this->m_settings.vsync = vsync;
    glfwSwapInterval(this->m_settings.vsync);
}

const GladGLContext* const ikk::Window::getContext() const noexcept
{
    return this->m_context;
}

const std::queue<ikk::Event>& ikk::Window::getEventQueue() const noexcept
{
    return this->m_events.getEventQueue();
}

std::queue<ikk::Event>& ikk::Window::getEventQueue() noexcept
{
    return this->m_events.getEventQueue();
}

GLFWwindow* const ikk::Window::create(const std::string_view title, const VideoMode vm) const noexcept
{
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return glfwCreateWindow(vm.width, vm.height, title.data(), NULL, NULL);
}

void ikk::Window::initWindowEvents() noexcept
{
    glfwSetWindowUserPointer(this->m_window, reinterpret_cast<void*>(this));
    
    static auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
        {
            Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
            handler->getContext()->Viewport(0, 0, width, height);
            handler->getEventQueue().emplace(Event::Type::FrameBufferResized, Event::SizeEvent{ static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) });
        };
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

    //TODO:
    //Impl rest of them...
}