#include "InariKonKon.hpp"

#include "TestScene.h"

int main()
{
	try
	{
		ikk::Application app{ "Test", { 500, 500 } };
		app.addScene(TestScene(&app));
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