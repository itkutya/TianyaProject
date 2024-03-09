#include "Window/Window.h"

#include <exception>

#include "glad/glad.h"
#define GLFW_INCLUDE_NONE
#define GLFW_DLL
#include "GLFW/glfw3.h"

Window::Window(const char* const title) : m_title(title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    this->m_window = glfwCreateWindow(600, 600, title, NULL, NULL);
    if (this->m_window == nullptr)
        throw std::exception("Error while creating window.");

    glfwMakeContextCurrent(this->m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::exception("Error cannot load openGL.");
}

Window::~Window() noexcept
{
    glfwTerminate();
}

const bool Window::shouldClose() const noexcept
{
    return glfwWindowShouldClose(this->m_window);
}

void Window::handleEvents() noexcept
{
    glfwPollEvents();
}

void Window::update() noexcept
{
}

void Window::render() noexcept
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(this->m_window);
}