#include "InariKonKon.hpp"

#include "InariKonKon/Graphics/Shapes/Triangle.hpp"
#include "InariKonKon/Graphics/Shapes/Quad.hpp"

class TestScene final : public ikk::Scene
{
public:
	TestScene(ikk::Application& app) noexcept : ikk::Scene(app, ikk::PostEffects::None) {};

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
		ikk::RenderState state{ &ikk::Shader::getDefaultShaderProgram(), &texture, &camera };
		window.draw(quad, state);
		window.draw(triangle, state);
	};
private:
	ikk::Triangle3D triangle;
	ikk::Quad3D quad;
	ikk::Texture texture{ std::filesystem::path("wall.jpg") };
	ikk::Camera<ikk::Projection::Orhto> camera{};
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
			app.updateVectors();
			app.render({ 0.2f, 0.1f, 0.6f });
		}
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}