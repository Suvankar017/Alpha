#include "pch.h"
#include "GLAD.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Alpha
{
	bool GLAD::s_IsInitialized = false;

	void GLAD::Init()
	{
		if (s_IsInitialized) return;

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			AP_ERROR("Failed to load GLAD");
			return;
		}

		AP_INFO("GLAD loaded successfully");
		s_IsInitialized = true;
	}
}