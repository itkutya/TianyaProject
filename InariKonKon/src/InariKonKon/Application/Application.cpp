#include "InariKonKon/Application/Application.hpp"

#include <thread>

ikk::Application::Application(const std::string_view title, const Window::Settings settings) noexcept : m_window(title.data(), settings)
{
	this->m_clock.restart();
}

const bool ikk::Application::isOpen() const noexcept
{
	return !this->m_window.shouldClose();
}

const ikk::Window& ikk::Application::getWindow() const noexcept
{
	return this->m_window;
}

ikk::Window& ikk::Application::getWindow() noexcept
{
	return this->m_window;
}

const ikk::priv::SceneManager& ikk::Application::getSceneManager() const noexcept
{
	return this->m_sceneManager;
}

ikk::priv::SceneManager& ikk::Application::getSceneManager() noexcept
{
	return this->m_sceneManager;
}

void ikk::Application::handleEvents() noexcept
{
	this->m_window.handleEvents();
	std::queue<Event>& eventQueue = this->m_window.getEventManager().getEventQueue();
	for (; !eventQueue.empty(); eventQueue.pop())
		this->m_sceneManager.getActiveScene().handleEvents(eventQueue.front());
}

void ikk::Application::updateVectors() noexcept
{
	const Time& dt = this->m_clock.restart();
	this->m_sceneManager.getActiveScene().update(dt);
}

//TODO:
//Clean up...
void ikk::Application::render(const Color clearColor) const noexcept
{
	this->m_window.clear(clearColor);

	if (this->m_sceneManager.getActiveScene().getPostFXManager().getActiveEffetcts() != PostEffects::None)
	{
		this->m_sceneManager.getActiveScene().getPostFXManager().clear();
		this->m_sceneManager.getActiveScene().getPostFXManager().getFrameBuffer().bind();
	}
	else
		this->m_sceneManager.getActiveScene().getPostFXManager().setDefaultFrameBuffer();

	this->m_sceneManager.getActiveScene().render(this->m_window);
	this->m_sceneManager.getActiveScene().getPostFXManager().render(this->m_window);
	this->m_window.render();

	if (const std::uint32_t limit = this->m_window.getFPSLimit(); limit > 0)
	{
		const std::int64_t targetFPS = static_cast<std::int64_t>(1000000LL / limit);
		const std::int64_t sleepTime = targetFPS - this->m_clock.getElapsedTime().asMicroseconds();
		if (sleepTime > 0)
			std::this_thread::sleep_for(std::chrono::microseconds(sleepTime));
	}
}