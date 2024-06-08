#include "InariKonKon/Window/Window.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "InariKonKon/Graphics/OpenGL.hpp"

inline static std::uint32_t s_uniqueID = 0;

ikk::Window::Window(const std::string& title, const Window::Settings settings)
try : m_id(++s_uniqueID), m_title(title), m_settings(settings), m_window(create(title, settings.videomode))
{
    if (this->m_window == nullptr)
        throw std::exception("Cannot create window.");

    glfwMakeContextCurrent(this->m_window);
    priv::Context::getInstance().addContext(this->m_id);
    this->setActive();

    if (!gladLoadGLContext(priv::Context::getInstance().getActiveContext().get(), glfwGetProcAddress))
        throw std::exception("Error cannot load openGL.");

    gl->Viewport(0, 0, settings.videomode.width, settings.videomode.height);
    
    this->setFPSLimit(settings.fpslimit);
    this->setVSync(settings.vsync);
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
}

const bool ikk::Window::shouldClose() const noexcept
{
	return glfwWindowShouldClose(this->m_window);
}

void ikk::Window::handleEvents() const noexcept
{
    glfwPollEvents();
}

void ikk::Window::clear(const Color clearColor) const noexcept
{
    this->setActive();
    gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
    gl->ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void ikk::Window::render() const noexcept
{
    this->setActive();
    glfwSwapBuffers(this->m_window);
}

const std::uint32_t ikk::Window::getFPSLimit() const noexcept
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

//Vsync only works if nvidia driver allows it LOL.
void ikk::Window::setVSync(const bool vsync) noexcept
{
    this->m_settings.fpslimit = (vsync == true) ? 0 : this->m_settings.fpslimit;
    this->m_settings.vsync = vsync;
    glfwSwapInterval(this->m_settings.vsync);
}

const std::string& ikk::Window::getTitle() const noexcept
{
    return this->m_title;
}

void ikk::Window::setTitle(const std::string& title) noexcept
{
    glfwSetWindowTitle(this->m_window, title.c_str());
}

const ikk::Vector2<std::uint32_t> ikk::Window::getSize() const noexcept
{
    return { this->m_settings.videomode.width, this->m_settings.videomode.height };
}

void ikk::Window::setSize(const Vector2<std::uint32_t> size) noexcept
{
    glfwSetWindowSize(this->m_window, size.x, size.y);
}

const float ikk::Window::getAspectRatio() const noexcept
{
    return static_cast<float>(this->getSize().x) / static_cast<float>(this->getSize().y);
}

void ikk::Window::draw(const Primitive type, const std::size_t count, const int offset) const noexcept
{
    gl->Enable(GL_DEPTH_TEST);
    gl->DrawArrays(type, offset, static_cast<GLsizei>(count));
}

void ikk::Window::draw(const Primitive type, const std::size_t indiciesCount, const GLType eboType) const noexcept
{
    gl->Enable(GL_DEPTH_TEST);
    gl->DrawElements(type, static_cast<GLsizei>(indiciesCount), eboType, 0);
}

const ikk::priv::EventManager& ikk::Window::getEventManager() const noexcept
{
    return this->m_eventManager;
}

ikk::priv::EventManager& ikk::Window::getEventManager() noexcept
{
    return this->m_eventManager;
}

void ikk::Window::setActive(const bool active) const noexcept
{
    if (active)
    {
        if (priv::Context::getInstance().getWindowIDForTheActiveContext() != this->m_id)
        {
            glfwMakeContextCurrent(this->m_window);
            priv::Context::getInstance().activateContextForWindow(this->m_id);
        }
    }
    else
        priv::Context::getInstance().activateContextForWindow(0);
}

GLFWwindow* const ikk::Window::create(const std::string& title, const VideoMode vm) const noexcept
{
    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return glfwCreateWindow(vm.width, vm.height, title.c_str(), NULL, NULL);
}

void ikk::Window::initWindowEvents() noexcept
{
    glfwSetWindowUserPointer(this->m_window, reinterpret_cast<void*>(this));
    
    static auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height)
        {
            Window* handler = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
            handler->setActive();
            gl->Viewport(0, 0, width, height);
            handler->getEventManager().getEventQueue().emplace(Event::Projection::FrameBufferResized, Event::SizeEvent{static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height)});
        };
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);
    //TODO:
    //Impl rest of them...
}