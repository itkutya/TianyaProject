#pragma once

#include "InariKonKon.hpp"

#include "InariKonKon/Graphics/Shader/Shader.hpp"

inline static const char* vertex =	"\
									#version 460 core\n\
									void main()\
									{\
									}";

inline static const char* fragment = "\
									#version 460 core\n\
									void main()\
									{\
									}";

class TestScene : public ikk::Scene
{
public:
	TestScene(ikk::Application* const app) noexcept : ikk::Scene(app) 
	{
		ikk::Shader shader(vertex, fragment);
	};

	TestScene(const TestScene&) noexcept = default;
	TestScene(TestScene&) noexcept = default;
	TestScene(TestScene&&) noexcept = default;

	virtual TestScene& operator=(const TestScene&) noexcept = default;
	virtual TestScene& operator=(TestScene&) noexcept = default;
	virtual TestScene& operator=(TestScene&&) noexcept = default;

	virtual ~TestScene() noexcept = default;

	virtual void handleEvents(const ikk::Event& event) noexcept {};
	virtual void update(const ikk::Time& dt) noexcept {};
	virtual void render(ikk::Window& window) noexcept {};
private:
};