#include "Application.hpp"

int main()
{
	Application app{ "Test" };
	while (!app.shouldClose())
	{
		app.handleEvents();
		app.update();
		app.draw();
	}
	return 0;
}