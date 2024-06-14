import InariKonKon;

import Texture;
import Camera;
import Shader;

import Triangle;
import Quad;

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app)
	{
	};

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
		ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Ortho> state{ .texture = &texture, .camera = &camera };
		window.draw(quad, state);
		window.draw(triangle, state);
	};
private:
	ikk::Quad2D quad{};
	ikk::Triangle2D triangle{};
	ikk::Texture texture{ "wall.jpg" };
	ikk::Camera<ikk::Projection::Ortho> camera{};
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