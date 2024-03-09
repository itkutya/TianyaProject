#include "Application/Application.hpp"

int main()
{
	try
	{
		Application app{ "Test" };
		while (app.getWindow().shouldClose() == false)
		{
			app.getWindow().handleEvents();
			app.getWindow().update();
			app.getWindow().render();
		}
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}