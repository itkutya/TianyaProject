#include "TestScene.h"

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