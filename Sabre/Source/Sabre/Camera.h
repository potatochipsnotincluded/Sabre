#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sabre {

	class Camera
	{
	public:
		Camera(glm::vec3 position, glm::vec3 rotation, float FOV, bool perspective, float near, float far);

		void ChangeProjection(float FOV, bool perspective, float near, float far);

		glm::mat4 GetView();
		glm::mat4 GetProjection();
	public:
		glm::vec3 Position;
		glm::vec3 Rotation;
	private:
		glm::mat4 m_Projection;
	};

	inline Camera* g_MainCamera;

}