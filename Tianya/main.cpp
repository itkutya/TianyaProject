#include "InariKonKon/InariKonKon.hpp"

#include "InariKonKon/Graphics/Texture/Texture.hpp"
#include "InariKonKon/Graphics/Shapes/Triangle.hpp"
#include "InariKonKon/Graphics/UI/Text/Text.hpp"

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app, ikk::PostEffects::All)
	{
		text.setFont(font2);
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
		//TODO:
		//Fix wrong depth stuff w/ diff cameras...
		ikk::RenderState<ikk::Dimension::_2D, ikk::Projection::Ortho> state1{ .texture = &texture1, .camera = &ortho };
		ikk::RenderState<ikk::Dimension::_3D, ikk::Projection::Perspective> state2{ .texture = &texture2, .camera = &perspective };
		ikk::RenderState<ikk::Dimension::_GUI, ikk::Projection::Ortho> UISate{ .camera = &screen };

		window.draw(quad, state1);
		window.draw(triangle, state2);
		window.draw(text, UISate);
	};
private:
	ikk::Quad2D quad{ ikk::vec3f{ 0.f, 0.f, -3.f }, ikk::vec2f{ (float)getApplication().getWindow().getSize().x, (float)getApplication().getWindow().getSize().y }};
	ikk::Triangle3D triangle{ ikk::vec3f{ 0.f, 0.f, -2.f }};
	//TODO:
	//not setting texture breakes it...
	ikk::Texture texture1{ "wall.jpg" };
	ikk::Texture texture2{ "doge.jpg" };
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