#pragma once

#include <string>

class Application final
{
public:
	Application(const char* const title) noexcept;

	Application(const Application&) noexcept = default;
	Application(Application&) noexcept = default;
	Application(Application&&) noexcept = default;
	
	Application& operator=(const Application&) noexcept = default;
	Application& operator=(Application&) noexcept = default;
	Application& operator=(Application&&) noexcept = default;

	~Application() noexcept = default;

	const bool shouldClose() const noexcept;

	void handleEvents() noexcept;
	void update() noexcept;
	void draw() noexcept;
private:
	std::string m_title;
};