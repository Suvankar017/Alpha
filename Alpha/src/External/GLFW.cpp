#include "pch.h"
#include "GLFW.h"

#include <GLFW/glfw3.h>

namespace Alpha
{
	bool GLFW::s_IsInitialized = false;

	void GLFW::Init()
	{
		if (s_IsInitialized) return;

		glfwSetErrorCallback([](int errorCode, const char* description)
		{
			AP_ERROR("Error : {}\nMessage : {}", errorCode, description);
		});

		if (!glfwInit())
		{
			AP_ERROR("Failed to initialize GLFW");
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		AP_INFO("GLFW initialized successfully");
		s_IsInitialized = true;
	}

	void GLFW::Shutdown()
	{
		glfwTerminate();
		AP_INFO("GLFW terminated");
	}
}