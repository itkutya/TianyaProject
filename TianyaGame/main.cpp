#include "Menu.hpp"

int main()
{
	try
	{
		ikk::Application app{ "Test", { 500, 500 } };
		app.getSceneManager().add<Menu>(false, app);
		while (app.isOpen())
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