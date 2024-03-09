#include "Application/Application.hpp"

int main()
{
	try
	{
		ikk::Application app{ "Test", { 500, 500 } };
		while (app.shouldClose() == false)
		{
			app.handleEvents();
			app.update();
			app.render();
		}
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}