#include "RendererGL41.h"
#include "Sabre/Window.h"

namespace Sabre {

	namespace GL41 {

		void Initialise()
		{
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				SABRE_ASSERT(false, "Failed to initialize GLAD!");
			}

            glEnable(GL_DEPTH_TEST);
		}

		void Shutdown() {}

		void ClearScreen(glm::vec4 colour)
		{
            glViewport(0, 0, Sabre::Window::GetWindowSize().x, Sabre::Window::GetWindowSize().y);

			glClearColor(colour.r, colour.g, colour.b, colour.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		GLMeshData CreateMesh(std::vector<float> vertices, std::vector<float> textureCoords,std::vector<float> normals, std::vector<uint32_t> indices)
		{
			GLMeshData mesh = GLMeshData();
            glGenVertexArrays(1, &mesh.VAO);
            glGenBuffers(1, &mesh.VBO);
            glGenBuffers(1, &mesh.TBO);
            glGenBuffers(1, &mesh.EBO);
            glGenBuffers(1, &mesh.NBO);

            glBindVertexArray(mesh.VAO);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);
            glBufferData(GL_ARRAY_BUFFER,
                vertices.size() * sizeof(float),
                vertices.data(),
                GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.TBO);
            glBufferData(GL_ARRAY_BUFFER,
                textureCoords.size() * sizeof(float),
                textureCoords.data(),
                GL_STATIC_DRAW);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

            glBindBuffer(GL_ARRAY_BUFFER, mesh.NBO);
            glBufferData(GL_ARRAY_BUFFER,
                normals.size() * sizeof(float),
                normals.data(),
                GL_STATIC_DRAW);
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); 

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                indices.size() * sizeof(uint32_t),
                indices.data(),
                GL_STATIC_DRAW);

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
			return mesh;
		}

        void BindMesh(GLMeshData mesh)
        {
            glBindVertexArray(mesh.VAO);
        }

        void UnbindMesh()
        {
            glBindVertexArray(0);
        }

        void RenderMesh(Mesh mesh, ShaderProgramme shaderProgramme, Texture* texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera camera)
        {
            shaderProgramme.Start();
            mesh.Bind();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
            model = glm::scale(model, scale);

            int32_t modelLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "model");
            int32_t viewLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "view");
            int32_t projLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "projection");
            int32_t textureLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "uTexture");

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetView()));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

            texture->SetActiveSlot(0);
            texture->Bind();

            glUniform1i(textureLoc, 0);

            glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, (void*)0);

            texture->Unbind();

            mesh.Unbind();
            shaderProgramme.End();
        }

        void RenderMeshPBR(Mesh mesh, ShaderProgramme shaderProgramme, Material* material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera camera)
        {
            shaderProgramme.Start();
            mesh.Bind();

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, position);
            model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1, 0, 0));
            model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0, 1, 0));
            model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0, 0, 1));
            model = glm::scale(model, scale);

            int32_t modelLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "model");
            int32_t viewLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "view");
            int32_t projLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "projection");
            int32_t textureLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "uTexture");

            int32_t lightDirectionLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "lightDir");
            int32_t lightColourLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "lightColour");
            int32_t lightIntensityLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "lightIntensity");
            int32_t ambientIntensityLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "ambientIntensity");

            int32_t viewPosLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "viewPos");

            int32_t metallicLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "metallic");
            int32_t smoothnessLoc = glGetUniformLocation(shaderProgramme.GetGLID(), "smoothness");

            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.GetView()));
            glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.GetProjection()));

            material->Albedo.SetActiveSlot(0);
            material->Albedo.Bind();

            glUniform1i(textureLoc, 0);

            glUniform3f(viewPosLoc, camera.Position.x, camera.Position.y, camera.Position.z);

            glUniform3f(lightDirectionLoc, GetSunLight()->Direction.x, GetSunLight()->Direction.y, GetSunLight()->Direction.z);
            glUniform3f(lightColourLoc, GetSunLight()->Colour.x, GetSunLight()->Colour.y, GetSunLight()->Colour.z);
            glUniform1f(lightIntensityLoc, GetSunLight()->Intensity);
            glUniform1f(ambientIntensityLoc, GetSunLight()->AmbientIntensity);

            glUniform1f(metallicLoc, material->Metallic);
            glUniform1f(smoothnessLoc, material->Smoothness);

            glDrawElements(GL_TRIANGLES, mesh.GetIndexCount(), GL_UNSIGNED_INT, (void*)0);

            material->Albedo.Unbind();

            mesh.Unbind();
            shaderProgramme.End();
        }

	}

}

