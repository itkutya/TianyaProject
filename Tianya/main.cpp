#include "InariKonKon/InariKonKon.hpp"

//Entity components system -> no -> too much for this scale of game engine
//Entity -> application should keep an eye on them or smthg...

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app/*, ikk::PostEffects::All*/)
	{
	};

	TestScene(const TestScene&) noexcept = default;
	TestScene(TestScene&&) noexcept = default;

	TestScene& operator=(const TestScene&) noexcept = default;
	TestScene& operator=(TestScene&&) noexcept = default;

	~TestScene() noexcept = default;

	void handleEvents(const ikk::Event& event) noexcept override
	{
	};

	void update(const ikk::Time& dt) noexcept override
	{
	};

	void render(const ikk::Window& window) const noexcept override
	{
		window.draw(quad, ikk::RenderState{ .texture = &wall, .camera = &mainCamera });
		window.draw(triangle);
	};
private:
	ikk::Quad2D quad{ { 0.f, 0.f, -2.f } };
	ikk::Triangle3D triangle{ { 0.f, 0.f, -1.f } };
	ikk::Camera<ikk::Projection::Perspective> mainCamera;
	ikk::Texture wall{ "wall.jpg" };
};

int main()
{
	try
	{
		ikk::Application app = { u8"日本", ikk::Window::Settings{ .size = { 500, 600 }, .vsync = true, .fullscreen = false } };
		app.getSceneManager().add(TestScene(app));
		app.run(ikk::Color::Cyan);
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}