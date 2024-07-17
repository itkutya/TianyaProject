#include "InariKonKon/InariKonKon.hpp"

class TestEntity : public ikk::Entity
{
	public:
	TestEntity()
	{
		ikk::EntityComponentSystem::getInstance().add<ikk::TransformComponent>(this);
		ikk::EntityComponentSystem::getInstance().add<ikk::MeshComponent>(this);

		auto conatins = this->contains<ikk::MeshComponent>();
	}

	void draw() const noexcept override
	{
	}
};

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
		//TODO:
		//Fix wrong depth stuff w/ diff cameras...
		window.draw(&ent, ikk::RenderState{ .camera = &mainCamera });
	};
private:
	TestEntity ent{};
	//TODO:
	//not setting texture breakes it...
	ikk::Texture texture1{ "wall.jpg" };
	ikk::Texture texture2{ "doge.jpg" };
	ikk::Camera<ikk::Projection::Perspective> mainCamera{};
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