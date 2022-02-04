#include "pch.h"
#include "Alpha/Manager/InputManager.h"

#include <GLFW/glfw3.h>

#include "Alpha/Event/KeyEvent.h"
#include "Alpha/Event/MouseEvent.h"
#include "Alpha/Platform/WindowsInput.h"

namespace Alpha
{
	Input* Input::s_Instance = nullptr;
	InputManager* InputManager::s_Instance = nullptr;

	void InputManager::Init(void* context)
	{
		if (s_Instance != nullptr) return;
		s_Instance = new InputManager();

		if (Input::s_Instance != nullptr) return;
		Input::s_Instance = new WindowsInput();

		AP_INFO("Input Manager initialized successfully");
		InitCallbacks(context);
	}

	void InputManager::Shutdown()
	{
		if (Input::s_Instance != nullptr) delete Input::s_Instance;
		if (s_Instance != nullptr) delete s_Instance;
		Input::s_Instance = nullptr;
		s_Instance = nullptr;

		AP_INFO("Input Manager shutdown");
	}
	
	void InputManager::OnEvent(Event& event)
	{
		Input::s_Instance->OnEvent(event);
	}

	void InputManager::PollEvents()
	{
		Input::s_Instance->OnReset();
		glfwPollEvents();
	}

	void InputManager::InitCallbacks(void* context)
	{
		if (context == nullptr)
		{
			AP_ERROR("Failed to initialize key callbacks (Context is NULL)");
			return;
		}

		GLFWwindow* window = static_cast<GLFWwindow*>(context);

		if (window == nullptr)
		{
			AP_ERROR("Failed to initialize key callbacks (Window is NULL)");
			return;
		}
		
		glfwSetKeyCallback(window, [](GLFWwindow* win, int key, int scancode, int action, int mods)
		{
			EventCallbackFunc& callback = s_Instance->m_Callback;
			switch (action)
			{
				case GLFW_PRESS:
				{
					if (callback)
					{
						KeyPressedEvent* e = new KeyPressedEvent(key, 0);
						callback(e);
					}
					else
					{
						AP_ERROR("Unable to raise event (KeyPressedEvent). Do you forget to set event callback?");
					}
					break;
				}
				case GLFW_REPEAT:
				{
					if (callback)
					{
						KeyPressedEvent* e = new KeyPressedEvent(key, 1);
						callback(e);
					}
					else
					{
						AP_ERROR("Unable to raise event (KeyPressedEvent). Do you forget to set event callback?");
					}
					break;
				}
				case GLFW_RELEASE:
				{
					if (callback)
					{
						KeyReleasedEvent* e = new KeyReleasedEvent(key);
						callback(e);
					}
					else
					{
						AP_ERROR("Unable to raise event (KeyReleasedEvent). Do you forget to set event callback?");
					}
					break;
				}
			}
		});
		
		glfwSetCharCallback(window, [](GLFWwindow* win, unsigned int codepoint)
		{
			EventCallbackFunc& callback = s_Instance->m_Callback;
			if (callback)
			{
				KeyTypedEvent* e = new KeyTypedEvent((char)codepoint);
				callback(e);
			}
			else
			{
				AP_ERROR("Unable to raise event (KeyTypedEvent). Do you forget to set event callback?");
			}
		});

		glfwSetCursorPosCallback(window, [](GLFWwindow* win, double xPos, double yPos)
		{
			EventCallbackFunc& callback = s_Instance->m_Callback;
			if (callback)
			{
				MouseMovedEvent* e = new MouseMovedEvent((float)xPos, (float)yPos);
				callback(e);
			}
			else
			{
				AP_ERROR("Unable to raise event (MouseMovedEvent). Do you forget to set event callback?");
			}
		});

		glfwSetCursorEnterCallback(window, [](GLFWwindow* win, int entered)
		{
			EventCallbackFunc& callback = s_Instance->m_Callback;
			if (entered)
			{
				if (callback)
				{
					MouseEnterEvent* e = new MouseEnterEvent();
					callback(e);
				}
				else
				{
					AP_ERROR("Unable to raise event (MouseEnterEvent). Do you forget to set event callback?");
				}
			}
			else
			{
				if (callback)
				{
					MouseExitEvent* e = new MouseExitEvent();
					callback(e);
				}
				else
				{
					AP_ERROR("Unable to raise event (MouseExitEvent). Do you forget to set event callback?");
				}
			}
		});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* win, int button, int action, int mods)
		{
			EventCallbackFunc& callback = s_Instance->m_Callback;
			switch (action)
			{
				case GLFW_PRESS:
				{
					if (callback)
					{
						MouseButtonPressedEvent* e = new MouseButtonPressedEvent(button);
						callback(e);
					}
					else
					{
						AP_ERROR("Unable to raise event (MouseButtonPressedEvent). Do you forget to set event callback?");
					}
					break;
				}
				case GLFW_RELEASE:
				{
					if (callback)
					{
						MouseButtonReleasedEvent* e = new MouseButtonReleasedEvent(button);
						callback(e);
					}
					else
					{
						AP_ERROR("Unable to raise event (MouseButtonReleasedEvent). Do you forget to set event callback?");
					}
					break;
				}
			}
		});

		glfwSetScrollCallback(window, [](GLFWwindow* win, double xOffset, double yOffset)
		{
			EventCallbackFunc& callback = s_Instance->m_Callback;
			if (callback)
			{
				MouseScrolledEvent* e = new MouseScrolledEvent((float)xOffset, (float)yOffset);
				callback(e);
			}
			else
			{
				AP_ERROR("Unable to raise event (MouseScrolledEvent). Do you forget to set event callback?");
			}
		});

		AP_INFO("Key callbacks initialized successfully");
	}
}