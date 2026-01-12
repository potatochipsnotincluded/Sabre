#pragma once
#include "Sabre/Data.h"
#include "Sabre/Debug.h"
#include "Sabre/Platform.h"

#include <string_view>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace Sabre {

	namespace Window {

		void Initialise(std::string_view title, int32_t width, int32_t height);
		void Shutdown();

		bool ShouldClose();
		void EndFrame();

		glm::ivec2 GetWindowSize();

		bool IsKeyDown(uint32_t key);

		void RequestQuit();

		// Private
		inline GLFWwindow* m_Window;

	}

}