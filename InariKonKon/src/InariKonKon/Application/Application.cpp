#include "InariKonKon/Application/Application.hpp"

ikk::Application::Application(const std::string_view title, const VideoMode vm)
try : m_window(title, vm)
{
}
catch (const std::exception& e)
{
	std::print("Exception was thrown while creating application.\nERROR: {}", e.what());
	throw e;
}

const bool ikk::Application::isOpen() const noexcept
{
	return !this->m_window.shouldClose();
}

void ikk::Application::handleEvents() noexcept
{
	this->m_window.handleEvents();
	for (; !this->m_window.getEventQueue().empty(); this->m_window.getEventQueue().pop())
	{
		if (this->m_sceneManager.getActiveScene() != nullptr)
			this->m_sceneManager.getActiveScene()->handleEvents(this->m_window.getEventQueue().front());
		else
			std::print("ERROR: Cannot handle events! There is no scene active on this application!\n");
	}
}

void ikk::Application::update() noexcept
{
	const Time& dt = this->m_clock.restart();

	if (this->m_sceneManager.getActiveScene() != nullptr)
		this->m_sceneManager.getActiveScene()->update(dt);
	else
		std::print("ERROR: Cannot update scene! There is no scene active on this application!\n");
}

void ikk::Application::render(const Color clearColor) noexcept
{
	this->m_window.clear(clearColor);

	if (this->m_sceneManager.getActiveScene() != nullptr)
		this->m_sceneManager.getActiveScene()->render(this->m_window);
	else
		std::print("ERROR: Cannot render scene! There is no scene active on this application!\n");

	this->m_window.render();
	
	if (const std::uint32_t& limit = this->m_window.getFPSLimit(); limit > 0)
		while (this->m_clock.getElapsedTime().toDuration() < std::chrono::microseconds(1000000 / limit));
}

void ikk::Application::removeScene(const ikk::Scene* scene, const bool resetActiveScene) noexcept
{
	this->m_sceneManager.remove(scene, resetActiveScene);
}

void ikk::Application::popLastScene(const bool resetActiveScene) noexcept
{
	this->m_sceneManager.pop(resetActiveScene);
}

ikk::Scene* const ikk::Application::setActiveScene(ikk::Scene* scene) noexcept
{
	return this->m_sceneManager.setActiveScene(scene);
}

const ikk::Scene* const ikk::Application::getActiveScene() const noexcept
{
	return this->m_sceneManager.getActiveScene();
}

ikk::Scene* const ikk::Application::getActiveScene() noexcept
{
	return this->m_sceneManager.getActiveScene();
}