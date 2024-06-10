#include "InariKonKon.hpp"

#include "InariKonKon/Graphics/Shapes/Triangle.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app, ikk::PostEffects::All) {};

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
	ikk::Camera<ikk::Projection::Perspective> perspective{};
};

int main()
{
	try
	{
		ikk::Application app{ "Test", ikk::Window::Settings{.videomode{ 500, 500 } } };
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