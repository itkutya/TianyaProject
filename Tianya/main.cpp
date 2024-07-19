﻿#include "InariKonKon/InariKonKon.hpp"

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
	};
private:
	//TODO:
	//not setting texture breakes it...
	//ikk::Texture texture1{ "wall.jpg" };
};

int main()
{
	try
	{
		ikk::Application app = { u8"日本", ikk::Window::Settings{ .size = { 500, 600 }, .fullscreen = false } };
		app.getSceneManager().add(TestScene(app));
		app.run(ikk::Color::Cyan);
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}