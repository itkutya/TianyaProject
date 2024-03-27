#include "InariKonKon/Window/Window.hpp"

#include <exception>
#include <print>

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#define GLFW_DLL
#include "GLFW/glfw3.h"

namespace ikk
{
    Window::Window(const char* const title, const glm::ivec2 size, const WindowSettigns settings)
    try : m_title(title), m_settings(settings), m_window(this->createWindow(title, size, settings))
    {
        if (this->m_window == nullptr)
            throw std::exception("Error while creating window.");

        glfwMakeContextCurrent(this->m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::exception("Error cannot load openGL.");

        this->initWindowForEvents();
        glfwSwapInterval(this->m_settings.vsync);
    }
    catch (const std::exception& e)
    {
        std::print("Exception was thrown: {}", e.what());
        throw std::exception(e);
    }

    Window::~Window() noexcept
    {
        glfwTerminate();
    }

    const std::queue<Event>& Window::getEventQueue() const noexcept
    {
        return this->m_eventManager.getEventQueue();
    }

    std::queue<Event>& Window::getEventQueue() noexcept
    {
        return this->m_eventManager.getEventQueue();
    }

    const bool Window::shouldClose() const noexcept
    {
        return glfwWindowShouldClose(this->m_window);
    }

    void Window::setFPSLimit(const std::uint32_t limit) noexcept
    {
        this->m_settings.fpslimit = limit;
        this->m_settings.vsync = limit != 0 ? false : true;
        glfwSwapInterval(this->m_settings.vsync);
    }

    const std::uint32_t Window::getFPSLimit() const noexcept
    {
        return this->m_settings.fpslimit;
    }

    void Window::setVSync(const bool vsync) noexcept
    {
        this->m_settings.fpslimit = vsync == true ? 0 : this->m_settings.fpslimit;
        this->m_settings.vsync = vsync;
        glfwSwapInterval(this->m_settings.vsync);
    }

    const bool Window::isVSyncEnabled() const noexcept
    {
        return this->m_settings.vsync;
    }

    void Window::handleEvents() noexcept
    {
        glfwPollEvents();
    }

    void Window::clear(const glm::vec4 clearColor) noexcept
    {
        glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::render() noexcept
    {
        glfwSwapBuffers(this->m_window);
    }

    GLFWwindow* const Window::createWindow(const char* const title, const glm::ivec2 size, const WindowSettigns settings) noexcept
    {
        if (!glfwInit())
            return nullptr;

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
        return glfwCreateWindow(size.x, size.y, title, NULL, NULL);
    }

    void Window::initWindowForEvents() noexcept
    {
        glfwSetWindowUserPointer(this->m_window, reinterpret_cast<void*>(&this->m_eventManager));
        static auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
            {
                glViewport(0, 0, width, height);
                priv::EventManager* manager = reinterpret_cast<priv::EventManager*>(glfwGetWindowUserPointer(window));
                manager->insert(Event(Event::Type::WindowFramebufferResized, Event::ResizeEvent{ static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) }));
            };

        glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
    }
}