#include "InariKonKon/Window/Window.hpp"

#include <exception>

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#define GLFW_DLL
#include "GLFW/glfw3.h"

#include "InariKonKon/Event/EventManager.hpp"

namespace ikk
{
    namespace priv
    {
        inline static priv::EventManager s_eventManager;

        //Window
        inline static void window_close_callback(GLFWwindow* window)
        {
            s_eventManager.insert(Event(Event::Type::WindowClosed));
        }

        inline static void window_size_callback(GLFWwindow* window, int width, int height)
        {
            s_eventManager.insert(Event(Event::Type::WindowResized));
        }

        inline static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
            s_eventManager.insert(Event(Event::Type::WindowFramebufferResized));
        }

        inline static void window_content_scale_callback(GLFWwindow* window, float xscale, float yscale)
        {
            s_eventManager.insert(Event(Event::Type::WindowContentScaleChanged));
        }

        inline static void window_pos_callback(GLFWwindow* window, int xpos, int ypos)
        {
            s_eventManager.insert(Event(Event::Type::WindowPositionChanged));
        }

        inline static void window_iconify_callback(GLFWwindow* window, int iconified)
        {
            if (iconified)
            {
                // The window was iconified
                s_eventManager.insert(Event(Event::Type::WindowIconified));
            }
            else
            {
                // The window was restored
                s_eventManager.insert(Event(Event::Type::WindowUnIconified));
            }
        }

        inline static void window_maximize_callback(GLFWwindow* window, int maximized)
        {
            if (maximized)
            {
                // The window was maximized
                s_eventManager.insert(Event(Event::Type::WindowMaximized));
            }
            else
            {
                // The window was restored
                s_eventManager.insert(Event(Event::Type::WindowUnMaximized));
            }
        }

        inline static void window_focus_callback(GLFWwindow* window, int focused)
        {
            if (focused)
            {
                // The window gained input focus
                s_eventManager.insert(Event(Event::Type::WindowFocused));
            }
            else
            {
                // The window lost input focus
                s_eventManager.insert(Event(Event::Type::WindowUnFocused));
            }
        }

        inline static void window_refresh_callback(GLFWwindow* window)
        {
            glfwSwapBuffers(window);
            s_eventManager.insert(Event(Event::Type::WindowRefreshed));
        }

        //Monitor
        inline static void monitor_callback(GLFWmonitor* monitor, int event)
        {
            if (event == GLFW_CONNECTED)
            {
                // The monitor was connected
                s_eventManager.insert(Event(Event::Type::MonitorConnected));
            }
            else if (event == GLFW_DISCONNECTED)
            {
                // The monitor was disconnected
                s_eventManager.insert(Event(Event::Type::MonitorDisconnected));
            }
        }

        //Input
        inline static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            s_eventManager.insert(Event(Event::Type::KeyPressed));
        }

        inline static void character_callback(GLFWwindow* window, unsigned int codepoint)
        {
            s_eventManager.insert(Event(Event::Type::CharacterTyped));
        }

        inline static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
        {
            s_eventManager.insert(Event(Event::Type::CursorPositionChanged));
        }

        inline static void cursor_enter_callback(GLFWwindow* window, int entered)
        {
            if (entered)
            {
                // The cursor entered the content area of the window
                s_eventManager.insert(Event(Event::Type::CursorEnteredWindow));
            }
            else
            {
                // The cursor left the content area of the window
                s_eventManager.insert(Event(Event::Type::CursorLeftWindow));
            }
        }

        inline static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
        {
            s_eventManager.insert(Event(Event::Type::MouseButtonPressed));
        }

        inline static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
        {
            s_eventManager.insert(Event(Event::Type::MouseWheelScrolled));
        }

        inline static void joystick_callback(int jid, int event)
        {
            if (event == GLFW_CONNECTED)
            {
                // The joystick was connected
                s_eventManager.insert(Event(Event::Type::JoystickConnected));
            }
            else if (event == GLFW_DISCONNECTED)
            {
                // The joystick was disconnected
                s_eventManager.insert(Event(Event::Type::JoystickDisconnected));
            }
        }

        inline static void drop_callback(GLFWwindow* window, int count, const char** paths)
        {
            s_eventManager.insert(Event(Event::Type::FileDropped));
        }

        inline static void initWindowForEvents(GLFWwindow* window)
        {
            //Window
            glfwSetWindowCloseCallback(window, window_close_callback);
            glfwSetWindowSizeCallback(window, window_size_callback);
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetWindowContentScaleCallback(window, window_content_scale_callback);
            glfwSetWindowPosCallback(window, window_pos_callback);
            glfwSetWindowIconifyCallback(window, window_iconify_callback);
            glfwSetWindowMaximizeCallback(window, window_maximize_callback);
            glfwSetWindowFocusCallback(window, window_focus_callback);
            //glfwSetWindowRefreshCallback(window, window_refresh_callback);
            //Monitor
            glfwSetMonitorCallback(monitor_callback);
            //Input
            glfwSetKeyCallback(window, key_callback);
            glfwSetCharCallback(window, character_callback);
            glfwSetCursorPosCallback(window, cursor_position_callback);
            glfwSetCursorEnterCallback(window, cursor_enter_callback);
            glfwSetMouseButtonCallback(window, mouse_button_callback);
            glfwSetScrollCallback(window, scroll_callback);
            glfwSetJoystickCallback(joystick_callback);
            glfwSetDropCallback(window, drop_callback);
        }
    }

    Window::Window(const char* const title, const glm::ivec2 size, const WindowSettigns settings) : m_title(title), m_settings(settings)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        this->m_window = glfwCreateWindow(size.x, size.y, title, NULL, NULL);

        if (this->m_window == nullptr)
            throw std::exception("Error while creating window.");

        glfwMakeContextCurrent(this->m_window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::exception("Error cannot load openGL.");

        priv::initWindowForEvents(this->m_window);
        glfwSwapInterval(this->m_settings.vsync);
    }

    Window::~Window() noexcept
    {
        glfwTerminate();
    }

    const std::queue<Event>& Window::getEventQueue() const noexcept
    {
        return priv::s_eventManager.getEventQueue();
    }

    std::queue<Event>& Window::getEventQueue() noexcept
    {
        return priv::s_eventManager.getEventQueue();
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
}