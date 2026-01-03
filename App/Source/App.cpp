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

	Sabre::ShaderProgramme shaderProgramme = Sabre::ShaderProgramme(Sabre::GetAssetFile("Assets/Shaders/testFrag.glsl"), Sabre::GetAssetFile("Assets/Shaders/testVert.glsl"));
    std::vector<float> vertices =
    {
        // Front face
        -0.5f, -0.5f,  0.5f, // 0
         0.5f, -0.5f,  0.5f, // 1
         0.5f,  0.5f,  0.5f, // 2
        -0.5f,  0.5f,  0.5f, // 3

        // Back face
        -0.5f, -0.5f, -0.5f, // 4
         0.5f, -0.5f, -0.5f, // 5
         0.5f,  0.5f, -0.5f, // 6
        -0.5f,  0.5f, -0.5f, // 7

        // Left face
        -0.5f, -0.5f, -0.5f, // 8
        -0.5f, -0.5f,  0.5f, // 9
        -0.5f,  0.5f,  0.5f, // 10
        -0.5f,  0.5f, -0.5f, // 11

        // Right face
         0.5f, -0.5f, -0.5f, // 12
         0.5f, -0.5f,  0.5f, // 13
         0.5f,  0.5f,  0.5f, // 14
         0.5f,  0.5f, -0.5f, // 15

         // Top face
         -0.5f,  0.5f,  0.5f, // 16
          0.5f,  0.5f,  0.5f, // 17
          0.5f,  0.5f, -0.5f, // 18
         -0.5f,  0.5f, -0.5f, // 19

         // Bottom face
         -0.5f, -0.5f,  0.5f, // 20
          0.5f, -0.5f,  0.5f, // 21
          0.5f, -0.5f, -0.5f, // 22
         -0.5f, -0.5f, -0.5f  // 23
    };

    std::vector<float> textureCoords =
    {
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // front
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // back
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // left
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // right
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f, // top
        0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f  // bottom
    };

    std::vector<uint32_t> indices =
    {
        0, 1, 2, 2, 3, 0,       // front
        4, 5, 6, 6, 7, 4,       // back
        8, 9, 10, 10, 11, 8,    // left
        12, 13, 14, 14, 15, 12, // right
        16, 17, 18, 18, 19, 16, // top
        20, 21, 22, 22, 23, 20  // bottom
    };



	Sabre::Mesh mesh = Sabre::Mesh(vertices, textureCoords, indices);

	Sabre::Camera camera = Sabre::Camera({ 0.0f, 0.0f, 5.0f }, { 0.0f, 0.0f, 0.0f }, 45, true, 0.1f, 100.0f);

	Sabre::Texture texture = Sabre::Texture(Sabre::GetAssetFile("Assets/container.jpg"));

	while (!Sabre::Window::ShouldClose())
	{
		if (Sabre::Window::IsKeyDown(SABRE_KEY_RIGHT))
			camera.Position.x += 0.001f;
		if (Sabre::Window::IsKeyDown(SABRE_KEY_LEFT))
			camera.Position.x -= 0.001f; 
		if (Sabre::Window::IsKeyDown(SABRE_KEY_UP))
			camera.Position.y += 0.001f;
		if (Sabre::Window::IsKeyDown(SABRE_KEY_DOWN))
			camera.Position.y -= 0.001f;

		Sabre::Renderer::ClearScreen({ 0.07f, 0.1f, 0.1f, 1.0f });

		Sabre::Renderer::RenderMesh(mesh, shaderProgramme, &texture, { 0, 0, 0 }, { 0,0,0 }, {1,1,1}, camera);

		Sabre::Window::EndFrame();
	}

	Sabre::Window::Shutdown();

	return 0;
}