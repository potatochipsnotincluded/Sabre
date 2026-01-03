#pragma once
#include "Platform.h"

#ifdef API_GL41
#include "GL41/RendererGL41.h"
#endif

#include "Sabre/Mesh.h"
#include "Sabre/ShaderProgramme.h"
#include "Sabre/Camera.h"
#include "Sabre/Texture.h"

#include <glm/glm.hpp>

namespace Sabre {

	namespace Renderer {

		inline void Initialise()
		{
#ifdef API_GL41
			GL41::Initialise();
#endif
		}

		inline void Shutdown()
		{
#ifdef API_GL41
			GL41::Shutdown();
#endif
		}

		inline void ClearScreen(glm::vec4 colour)
		{
#ifdef API_GL41
			GL41::ClearScreen(colour);
#endif
		}

		inline void RenderMesh(Mesh mesh, ShaderProgramme shader, Texture* texture, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Camera camera)
		{
#ifdef API_GL41
			GL41::RenderMesh(mesh, shader, texture, position, rotation, scale, camera);
#endif
		}
	}

}