#include "Application.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

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
			Sabre::Window::BeginFrame();

#ifdef API_GL41
			ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef WINDOWS
			ImGui_ImplGlfw_NewFrame();
#endif
			ImGui::NewFrame();
			ImGui::DockSpaceOverViewport(0U, 0, ImGuiDockNodeFlags_PassthruCentralNode);

			for (Layer* layer : m_Layers)
				layer->OnUpdate();

			for (Layer* layer : m_Layers)
				layer->OnRender();

			ImGui::Render();
#ifdef API_GL41
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
#endif
#ifdef WINDOWS
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
#endif

			Sabre::Window::EndFrame();
		}
	}

}
