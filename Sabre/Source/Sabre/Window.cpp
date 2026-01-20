#include "Window.h"

namespace Sabre {

	namespace Window {

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			m_ScrollOffset = yoffset;
		}

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

			glfwSetScrollCallback(m_Window, ScrollCallback);
		}

		void Shutdown()
		{
			glfwDestroyWindow(m_Window);
			glfwTerminate();
		}

		void BeginFrame()
		{
			m_LastFrameTime = glfwGetTime();
		}

		bool ShouldClose()
		{
			return glfwWindowShouldClose(m_Window);
		}

		void RequestQuit()
		{
			glfwSetWindowShouldClose(m_Window, true);
		}

		void EndFrame()
		{
			m_DeltaTime = glfwGetTime() - m_LastFrameTime;
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

		bool IsMouseDown(uint32_t button)
		{
			return glfwGetMouseButton(m_Window, button) == GLFW_PRESS;
		}

		glm::vec2 GetMousePosition()
		{
			double x;
			double y;

			glfwGetCursorPos(m_Window, &x, &y);
			return glm::vec2(x, y);
		}

		double GetScrollOffset()
		{
			int32_t prv = m_ScrollOffset;
			m_ScrollOffset = 0.0;
			return prv;
		}

		double GetDeltaTime()
		{
			return m_DeltaTime;
		}

	}

}

