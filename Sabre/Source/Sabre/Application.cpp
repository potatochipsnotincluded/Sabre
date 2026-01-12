#include "Application.h"

namespace Sabre {

	Layer::Layer(int argc, char* argv[])
	{
		ArgC = argc;
		ArgV = argv;
	}

	Application::~Application()
	{
		for (Layer* layer : m_Layers)
		{
			delete layer;
		}
	} 

	void Application::Run()
	{
		for (Layer* layer : m_Layers)
			layer->OnInit();
		while (!Sabre::Window::ShouldClose())
		{
			for (Layer* layer : m_Layers)
				layer->OnUpdate();

			for (Layer* layer : m_Layers)
				layer->OnRender();
		}
	}

}
