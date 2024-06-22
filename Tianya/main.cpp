<<<<<<< HEAD
﻿import InariKonKon;

import Texture;
import Camera;
import Shader;

import Triangle;
import Quad;
=======
#include "InariKonKon.hpp"

#include "InariKonKon/Graphics/Shapes/Triangle.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"
>>>>>>> master

class TestScene final : public ikk::Scene
{
public:
<<<<<<< HEAD
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app, ikk::PostEffects::All)
	{
	};
=======
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app, ikk::PostEffects::All) {};
>>>>>>> master

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
<<<<<<< HEAD
		ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Ortho> state1{ .texture = &texture, .camera = &ortho };
		window.draw(quad, state1);
		ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Perspective> state2{ .texture = &texture, .camera = &perspective };
		window.draw(triangle, state2);
	};
private:
	ikk::Quad2D quad{};
	ikk::Triangle2D triangle{};
	ikk::Texture texture{ "wall.jpg" };
	ikk::Camera<ikk::Projection::Ortho> ortho{};
=======
		ikk::RenderState state1{ &ikk::Shader::getDefaultShaderProgram(), &texture, &ortho };
		window.draw(quad, state1);
		ikk::RenderState state2{ &ikk::Shader::getDefaultShaderProgram(), &texture, &perspective };
		window.draw(triangle, state2);
	};
private:
	ikk::Triangle3D triangle;
	ikk::Quad3D quad;
	ikk::Texture texture{ std::filesystem::path("wall.jpg") };
	ikk::Camera<ikk::Projection::Orhto> ortho{};
>>>>>>> master
	ikk::Camera<ikk::Projection::Perspective> perspective{};
};

int main()
{
	try
	{
		ikk::Application app{ u8"日本", ikk::Window::Settings{ .videomode{ 500, 500 } } };
		app.getSceneManager().add<TestScene>(true, app);
		while (app.isOpen())
		{
			app.handleEvents();
			app.update();
			app.render({ 0.2f, 0.1f, 0.6f });
		}
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}