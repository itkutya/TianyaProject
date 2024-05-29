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
		//Dimension is temp...
		ikk::RenderState<ikk::Draw::Dimension::_2D> state{ &ikk::Shader::getDefaultShaderProgram(), &texture, &camera };
		window.draw(quad, state);
		window.draw(triangle, state);
	};
private:
	ikk::Triangle<ikk::Draw::Dimension::_2D> triangle;
	ikk::Quad quad;
	ikk::Texture texture{ std::filesystem::path("include/wall.jpg") };
	ikk::Camera<ikk::Projection::Perspective> camera{};
};