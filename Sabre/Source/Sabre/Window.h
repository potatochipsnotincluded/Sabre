#pragma once
#include "Sabre/Data.h"
#include "Sabre/Debug.h"
#include "Sabre/Platform.h"

#include <string_view>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Sabre {

	namespace Window {

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		void Initialise(std::string_view title, int32_t width, int32_t height);
		void Shutdown();

		void BeginFrame();

		bool ShouldClose();
		void EndFrame();

		glm::ivec2 GetWindowSize();

		bool IsKeyDown(uint32_t key);
		bool IsMouseDown(uint32_t button);

		glm::vec2 GetMousePosition();
		double GetScrollOffset();

		void RequestQuit();

		double GetDeltaTime();

		// Private
		inline GLFWwindow* m_Window;
		inline double m_ScrollOffset = 0.0;
		inline double m_LastFrameTime = 0.0;
		inline double m_DeltaTime = 0.0;

	}

}