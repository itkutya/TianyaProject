#pragma once

#include "InariKonKon.hpp"

#include "InariKonKon/Graphics/Shapes/Triangle.hpp"

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application* const app) noexcept : ikk::Scene(app, ikk::PostEffect::All) {};

	TestScene(const TestScene&) noexcept = default;
	TestScene(TestScene&&) noexcept = default;

	virtual TestScene& operator=(const TestScene&) noexcept = default;
	virtual TestScene& operator=(TestScene&&) noexcept = default;

	~TestScene() noexcept = default;

	void handleEvents(const ikk::Event& event) noexcept override {};
	void update(const ikk::Time& dt) noexcept override {};
	void render(ikk::Window& window) noexcept override
	{
		window.draw(triangle);
	};
private:
	ikk::Triangle triangle;
};