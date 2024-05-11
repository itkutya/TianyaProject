#include "InariKonKon/Window/Window.hpp"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "InariKonKon/Graphics/PostFX/Manager/PostFXManager.hpp"
#include "InariKonKon/Window/EventManager/EventManager.hpp"
#include "InariKonKon/Window/Context/Context.hpp"

inline static std::uint32_t s_uniqueID = 0;

ikk::Window::Window(const std::string& title, const Window::Settings settings)
try : m_id(++s_uniqueID), m_title(title), m_settings(settings), m_window(create(title, settings.videomode)), m_eventManager(std::make_shared<priv::EventManager>())
{
    if (this->m_window == nullptr)
        throw std::exception("Cannot create window.");

    glfwMakeContextCurrent(this->m_window);
    priv::Context::getInstance().addContext(this->m_id);
    this->setActive();

    if (!gladLoadGLContext(priv::Context::getInstance().getActiveContext().get(), glfwGetProcAddress))
        throw std::exception("Error cannot load openGL.");

    gl->Viewport(0, 0, settings.videomode.width, settings.videomode.height);
    
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

    this->setDefaultFrameBufferActive();
    gl->ClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    if (this->m_activeScene)
    {
        this->m_activeScene->m_postFXManager->getFrameBuffer().bind();
        gl->ClearColor(0.f, 0.f, 0.f, 0.f);
        gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    }
}

void ikk::Window::render() const noexcept
{
    this->setActive();
    
    if (this->m_activeScene)
        this->m_activeScene->m_postFXManager->render(*this);

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

const std::queue<ikk::Event>& ikk::Window::getEventQueue() const noexcept
{
    return this->m_eventManager->getEventQueue();
}

std::queue<ikk::Event>& ikk::Window::getEventQueue() noexcept
{
    return this->m_eventManager->getEventQueue();
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
            handler->getEventQueue().emplace(Event::Type::FrameBufferResized, Event::SizeEvent{ static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height) });
        };
    glfwSetFramebufferSizeCallback(this->m_window, framebuffer_size_callback);

    //TODO:
    //Impl rest of them...
}

void ikk::Window::setDefaultFrameBufferActive() const noexcept
{
    gl->BindFramebuffer(GL_FRAMEBUFFER, 0);
}