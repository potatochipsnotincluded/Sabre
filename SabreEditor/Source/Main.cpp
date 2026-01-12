#include "Sabre/Application.h"
#include "EditorLayer.h"

Sabre::Application* CreateApplication()
{
	Sabre::Window::Initialise("Sabre Engine", 1280, 720);
	Sabre::Renderer::Initialise();

	Sabre::Application* application = new Sabre::Application();
	application->PushLayer<EditorLayer>();

	return application;
}

void DestroyApplication(Sabre::Application* application)
{
	Sabre::Window::Shutdown();
}

#include "Sabre/EntryPoint.h"