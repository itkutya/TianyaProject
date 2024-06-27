#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/Graphics/Texture/Texture.hpp"

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app, ikk::PostEffects::All)
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
		//ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Ortho> state1{ .texture = &texture, .camera = &ortho };
		//window.draw(quad, state1);
		//ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Perspective> state2{ .texture = &texture, .camera = &perspective };
		//window.draw(triangle, state2);
	};
private:
	//ikk::Quad2D quad{};
	//ikk::Triangle2D triangle{};
	ikk::Texture texture{ "wall.jpg" };
	ikk::Camera<ikk::Projection::Ortho> ortho{};
	ikk::Camera<ikk::Projection::Perspective> perspective{};
};

int main()
{
	try
	{
		ikk::Application app = { u8"日本", ikk::Window::Settings{ .monitor = { 500, 500 } } };
		app.addScene(TestScene(app));
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