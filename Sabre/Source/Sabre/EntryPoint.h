#include "Application.h"

int main(int argc, char* argv[])
{
	Sabre::Application* application =CreateApplication();

	application->Run();

	DestroyApplication(application);
	delete application;
}