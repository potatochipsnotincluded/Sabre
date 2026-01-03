#include "Camera.h"
#include "Sabre/Window.h"

namespace Sabre {

	Camera::Camera(glm::vec3 Position, glm::vec3 Rotation, float FOV, bool perspective, float near, float far)
	{
		this->Position = Position;
		this->Rotation = Rotation;

		glm::vec2 size = Window::GetWindowSize();

		if (perspective)
		{
			float fov = glm::radians(FOV);
			float aspectRatio = size.x / size.y;
			float nearPlane = 0.1f;
			float farPlane = 100.0f;

			m_Projection = glm::perspective(fov, aspectRatio, near, far);
		}
		else
		{
			m_Projection = glm::ortho(0.0f, size.x, 0.0f, size.y, near, far);
		}
	}

	void Camera::ChangeProjection(float FOV, bool perspective, float near, float far)
	{
		glm::vec2 size = Window::GetWindowSize();

		if (perspective)
		{
			float fov = glm::radians(FOV);
			float aspectRatio = size.x / size.y;
			float nearPlane = 0.1f;
			float farPlane = 100.0f;

			m_Projection = glm::perspective(fov, aspectRatio, near, far);
		}
		else
		{
			m_Projection = glm::ortho(0.0f, size.x, 0.0f, size.y, near, far);
		}
	}

	glm::mat4 Camera::GetView()
	{
		glm::vec3 direction;
		direction.x = cos(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
		direction.y = sin(glm::radians(Rotation.x));
		direction.z = sin(glm::radians(Rotation.y)) * cos(glm::radians(Rotation.x));
		direction = glm::normalize(direction);

		// adjust yaw so 0 Rotation looks along -Z
		direction.x = sin(glm::radians(Rotation.y));        // X
		direction.z = -cos(glm::radians(Rotation.y));       // Z


		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

		glm::vec3 right = glm::normalize(glm::cross(direction, worldUp));
		glm::vec3 up = glm::normalize(glm::cross(right, direction));

		glm::mat4 view = glm::lookAt(
			Position,
			Position + direction,
			up
		);


		return view;
	}

	glm::mat4 Camera::GetProjection()
	{
		return m_Projection;
	}


}
