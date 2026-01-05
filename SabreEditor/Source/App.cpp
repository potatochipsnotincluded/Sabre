#include "Sabre/Sabre.h"

#include "imgui/imgui.h"

#ifdef WINDOWS
#include "imgui/imgui_impl_glfw.h"
#endif

#ifdef API_GL41
#include "imgui/imgui_impl_opengl3.h"
#endif

int main()
{
	SABRE_LOG(Severity::Debug, "Sabre Engine Initialising");
	SABRE_LOG(Severity::Debug, "Version: {}.{}.{}", SABRE_VERSION_MAJOR, SABRE_VERSION_MINOR, SABRE_VERSION_PATCH);
#ifdef API_GL41
	SABRE_LOG(Severity::Debug, "Using API: OpenGL 4.1");
#endif

	Sabre::Window::Initialise("Sabre Engine", 1280, 720);
	Sabre::Renderer::Initialise();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGui::StyleColorsDark();
	
#ifdef WINDOWS
#ifdef API_GL41
	ImGui_ImplGlfw_InitForOpenGL(Sabre::Window::m_Window, true);
#endif
#endif

#ifdef API_GL41
	ImGui_ImplOpenGL3_Init("#version 130");
#endif
	Sabre::SunLight sunLight = Sabre::SunLight(glm::normalize(glm::vec3(0.3f, 1.0f, 0.5f)), glm::vec3(1, 1, 1), 2, 0.1f);
	Sabre::SetSunLight(&sunLight);

	Sabre::ShaderProgramme shaderProgramme = Sabre::ShaderProgramme(Sabre::GetAssetFile("Assets/Shaders/pbrFragmentShader.glsl"), Sabre::GetAssetFile("Assets/Shaders/pbrVertexShader.glsl"));

	Sabre::Mesh mesh = Sabre::LoadMesh(Sabre::GetAssetFile("Assets/bunny.glb"));

	Sabre::Camera camera = Sabre::Camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, 45, true, 0.1f, 100.0f);

	Sabre::Material material = Sabre::Material(Sabre::GetAssetFile("Assets/bunnyTexture.jpeg"), 1.0f, 0.0f);

	glm::vec4 clearColour = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);

	while (!Sabre::Window::ShouldClose())
	{
		if (Sabre::Window::IsKeyDown(SABRE_KEY_D))
			camera.Position.x += 0.001f;
		if (Sabre::Window::IsKeyDown(SABRE_KEY_A))
			camera.Position.x -= 0.001f; 
		if (Sabre::Window::IsKeyDown(SABRE_KEY_W))
			camera.Position.y += 0.001f;
		if (Sabre::Window::IsKeyDown(SABRE_KEY_S))
			camera.Position.y -= 0.001f;
        if (Sabre::Window::IsKeyDown(SABRE_KEY_Q))
            camera.Position.z -= 0.001f;
        if (Sabre::Window::IsKeyDown(SABRE_KEY_E))
            camera.Position.z += 0.001f;

		Sabre::Renderer::ClearScreen(clearColour);

#ifdef API_GL41
		ImGui_ImplOpenGL3_NewFrame();
#endif
#ifdef WINDOWS
		ImGui_ImplGlfw_NewFrame();
#endif
		ImGui::NewFrame();
		static bool show_demo_window = true;

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		ImGui::Begin("Scene");

		float colour[4] = { clearColour.r, clearColour.g, clearColour.b, clearColour.a };

		ImGui::Text("Clear Colour: ");
		ImGui::SameLine();
		ImGui::ColorEdit4("###sceneclearcolour", colour);

		ImGui::Text("Ambient: ");
		ImGui::SameLine();
		ImGui::DragFloat("###sceneambient", &sunLight.AmbientIntensity, 0.025f);

		clearColour.r = colour[0];
		clearColour.g = colour[1];
		clearColour.b = colour[2];
		clearColour.a = colour[3];

		ImGui::End();

		Sabre::Renderer::RenderMeshPBR(mesh, shaderProgramme, &material, { 0, 0, 0 }, { 0, 0, 0 }, { 0.05f, 0.05f, 0.05f }, camera);

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

#ifdef API_GL41
	ImGui_ImplOpenGL3_Shutdown();
#endif
#ifdef WINDOWS
	ImGui_ImplGlfw_Shutdown();
#endif
	ImGui::DestroyContext();

	Sabre::Window::Shutdown();

	return 0;
}