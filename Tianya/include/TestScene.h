#pragma once

#include "InariKonKon.hpp"

#include "InariKonKon/Graphics/Shapes/Triangle.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app/*, ikk::PostEffects::All*/) {};

	TestScene(const TestScene&) noexcept = default;
	TestScene(TestScene&&) noexcept = default;

	virtual TestScene& operator=(const TestScene&) noexcept = default;
	virtual TestScene& operator=(TestScene&&) noexcept = default;

	~TestScene() noexcept = default;

	void handleEvents(const ikk::Event& event) noexcept override
	{
	};

	void update(const ikk::Time& dt) noexcept override
	{
	};

	void render(const ikk::Window& window) const noexcept override
	{
		ikk::RenderState state{ &ikk::Shader::getDefaultShaderProgram(), &texture, &camera, &triangle.getTransform() };
		window.draw(quad, state);
		window.draw(triangle, state);
	};
private:
	ikk::Triangle<ikk::Dimension::_2D> triangle;
	ikk::Quad<ikk::Dimension::_2D> quad;
	ikk::Texture texture{ std::filesystem::path("include/wall.jpg") };
	ikk::Camera<ikk::Projection::Orhto> camera{};
};