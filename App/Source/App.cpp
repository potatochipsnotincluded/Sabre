#include "Sabre/Sabre.h"

int main()
{
	SABRE_LOG(Severity::Debug, "Sabre Engine Initialising");
	SABRE_LOG(Severity::Debug, "Version: {}.{}.{}", SABRE_VERSION_MAJOR, SABRE_VERSION_MINOR, SABRE_VERSION_PATCH);
#ifdef API_GL41
	SABRE_LOG(Severity::Debug, "Using API: OpenGL 4.1");
#endif

	Sabre::Window::Initialise("Sabre Engine", 1280, 720);
	Sabre::Renderer::Initialise();

	Sabre::SunLight sunLight = Sabre::SunLight(glm::normalize(glm::vec3(0.3f, 1.0f, 0.5f)), glm::vec3(1, 1, 1), 2);
	Sabre::SetSunLight(&sunLight);

	Sabre::ShaderProgramme shaderProgramme = Sabre::ShaderProgramme(Sabre::GetAssetFile("Assets/Shaders/pbrFragmentShader.glsl"), Sabre::GetAssetFile("Assets/Shaders/pbrVertexShader.glsl"));

	Sabre::Mesh mesh = Sabre::LoadMesh(Sabre::GetAssetFile("Assets/bunny.glb"));

	Sabre::Camera camera = Sabre::Camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, 45, true, 0.1f, 100.0f);

	Sabre::Material material = Sabre::Material(Sabre::GetAssetFile("Assets/bunnyTexture.jpeg"), 1.0f, 0.0f);

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

		Sabre::Renderer::ClearScreen({ 0.42f, 0.8f, 0.89f, 1.0f });

		Sabre::Renderer::RenderMeshPBR(mesh, shaderProgramme, &material, { 0, 0, 0 }, { 0, 0, 0 }, { 0.05f, 0.05f, 0.05f }, camera);

		Sabre::Window::EndFrame();
	}

	Sabre::Window::Shutdown();

	return 0;
}