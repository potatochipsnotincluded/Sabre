#include "Window.h"

namespace Sabre {

	namespace Window {

		void Initialise(std::string_view title, int32_t width, int32_t height)
		{
			if (!glfwInit())
			{
				SABRE_ASSERT(false, "Failed to initialize GLFW!");
			}
#ifdef API_GL41
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
			m_Window = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);
			SABRE_ASSERT(m_Window, "Failed to create GLFW window!");

			glfwMakeContextCurrent(m_Window);
		}

		void Shutdown()
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		bool ShouldClose()
		{
			return glfwWindowShouldClose(m_Window);
		}

		void EndFrame()
		{
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}

		glm::ivec2 GetWindowSize()
		{
			glm::ivec2 size;
			glfwGetWindowSize(m_Window, &size.x, &size.y);
			return size;
		}

		bool IsKeyDown(uint32_t key)
		{
			return glfwGetKey(m_Window, key) == GLFW_PRESS;
		}

	}

}

