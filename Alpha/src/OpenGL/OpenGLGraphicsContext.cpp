#include "pch.h"
#include "Alpha/OpenGL/OpenGLGraphicsContext.h"

#include <GLFW/glfw3.h>

#include "../External/GLAD.h"

namespace Alpha
{
	GraphicsContext* GraphicsContext::Create(void* context)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(context);
		return new OpenGLGraphicsContext(window);
	}

	void GraphicsContext::Destroy(GraphicsContext*& context)
	{
		if (context == nullptr) return;
		delete context;
		context = nullptr;
	}

	OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* window) : m_Window(window)
	{
		glfwMakeContextCurrent(window);
		GLAD::Init();
	}

	void OpenGLGraphicsContext::SetCurrentContext(void* context)
	{
		m_Window = static_cast<GLFWwindow*>(context);
		glfwMakeContextCurrent(m_Window);
	}

	void OpenGLGraphicsContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}