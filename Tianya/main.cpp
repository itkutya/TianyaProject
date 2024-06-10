import InariKonKon;

int main()
{
	try
	{
		ikk::Application app{ "c++ modules version" };
		app.render();
	}
	catch (...)
	{
		return -1;
	}
	return 0;
}