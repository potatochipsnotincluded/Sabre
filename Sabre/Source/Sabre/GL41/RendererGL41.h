#pragma once
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>

#include "Sabre/Debug.h"
#include "Sabre/Mesh.h"
#include "Sabre/ShaderProgramme.h"
#include "Sabre/Camera.h"
#include "Sabre/Texture.h"
#include "Sabre/Light.h"
#include "Sabre/Material.h"

namespace Sabre {

	namespace GL41 {

		void Initialise();
		void Shutdown();

		void ClearScreen(glm::vec4 colour);

		GLMeshData CreateMesh(std::vector<float> vertices, std::vector<float> textureCoords, std::vector<float> normals, std::vector<uint32_t> indices);

		void BindMesh(GLMeshData mesh);
		void UnbindMesh();

		void RenderMesh(Mesh mesh, ShaderProgramme shaderProgramme, Texture* texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera camera);
		void RenderMeshPBR(Mesh mesh, ShaderProgramme shaderProgramme, Material* material, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera camera);

	}

}