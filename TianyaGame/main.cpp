#include "Menu.h"

int main()
{
	try
	{
		ikk::Application app{ "Test", { 500, 500 } };
		app.getStateManager().add<Menu>();
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