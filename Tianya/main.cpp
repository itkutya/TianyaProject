#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shapes/Triangle.hpp"
#include "InariKonKon/Graphics/UI/Text/Text.hpp"

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
		//OpenGL Object move constructor sets texture to 0, hence why you cant use it in the constuctor of scene
		//needs to be fixed...
		text.setFont(font2);
		ortho.update(dt);
		perspective.update(dt);
		//quad.getTransform().translate({ 50.f * dt.asSeconds(), 50.f * dt.asSeconds() });
	};

	void render(const ikk::Window& window) const noexcept override
	{
		//Depth is funcy...
		//Needs more research...
		ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Perspective> state1{ .texture = &texture, .camera = &perspective };
		window.draw(quad, state1);
		ikk::RenderState<ikk::Dimension::_3D, ikk::Projection::Perspective> state2{ .texture = &texture, .camera = &perspective };
		window.draw(triangle, state2);
		ikk::RenderState<ikk::Dimension::_GUI, ikk::Projection::Ortho> UISate{ .camera = &screen };
		window.draw(text, UISate);
	};
private:
	//TODO:
	//Figure out why is quad rendering upside down when used with a perspective proj...
	ikk::Quad2D quad{ ikk::vec3f{ 0.f, 0.f, -3.f }, ikk::vec2f{ 1.f, 1.f }, ikk::Color::White, { 0.f, 0.f, 1.f, 1.f } };
	ikk::Triangle3D triangle{ ikk::vec3f{ 0.f, 0.f, -2.f }, ikk::vec2f{ 1.f, 1.f } };
	ikk::Texture texture{ "wall.jpg" };
	ikk::Camera<ikk::Projection::Ortho> ortho{};
	ikk::Camera<ikk::Projection::Perspective> perspective{};
	ikk::Camera<ikk::Projection::Ortho> screen{};
	ikk::TextGUI text{ u8"The quick brown fox, jumped over the fence.", { 25.f, 250.f, -1.f }, 1.f, ikk::Color::Cyan };
	ikk::Font font1{ "Baefont_normal-Regular_V1.ttf" };
	ikk::Font font2{ "timesbd.ttf" };
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