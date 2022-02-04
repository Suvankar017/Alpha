#include "pch.h"
#include "Alpha/Platform/WindowsInput.h"

#include <GLFW/glfw3.h>

#include "Alpha/Macros.h"
#include "Alpha/Core/Engine.h"

namespace Alpha
{
	WindowsInput::WindowsInput()
	{
		m_XOffset = 0.0f;
		m_YOffset = 0.0f;
		m_IsKeyPressed = false;
		m_IsKeyReleased = false;
		m_PressedKey = -1;
		m_ReleasedKey = -1;

		AP_INFO("Windows Input created");
	}

	WindowsInput::~WindowsInput()
	{
		AP_INFO("Windows Input destroyed");
	}

	std::pair<float, float> WindowsInput::GetMousePosition()
	{
		double xPos, yPos;
		GLFWwindow* window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos, (float)yPos };
	}

	std::pair<float, float> WindowsInput::GetMouseScrollDelta()
	{
		return { m_XOffset, m_YOffset };
	}

	bool WindowsInput::GetKey(int key)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		return glfwGetKey(window, key) == GLFW_PRESS;
	}

	bool WindowsInput::GetKeyDown(int key)
	{
		return m_IsKeyPressed && m_PressedKey == key;
	}

	bool WindowsInput::GetKeyUp(int key)
	{
		return m_IsKeyReleased && m_ReleasedKey == key;
	}

	bool WindowsInput::GetMouseButton(int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Engine::Get().GetWindow().GetNativeWindow());
		return glfwGetMouseButton(window, button) == GLFW_PRESS;
	}

	bool WindowsInput::GetMouseButtonDown(int button)
	{
		return m_IsButtonPressed && m_PressedButton == button;
	}

	bool WindowsInput::GetMouseButtonUp(int button)
	{
		return m_IsButtonReleased && m_ReleasedButton == button;
	}

	void WindowsInput::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(WindowsInput::OnMouseScrolled));
		dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(WindowsInput::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(WindowsInput::OnKeyReleased));
		dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(WindowsInput::OnMouseButtonPressed));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(WindowsInput::OnMouseButtonReleased));
	}

	void WindowsInput::OnReset()
	{
		m_XOffset = m_YOffset = 0.0f;
		m_PressedKey = m_ReleasedKey = -1;
		m_PressedButton = m_ReleasedButton = -1;
		m_IsKeyPressed = m_IsKeyReleased = false;
		m_IsButtonPressed = m_IsButtonReleased = false;
	}

	bool WindowsInput::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_XOffset = e.GetXOffset();
		m_YOffset = e.GetYOffset();
		return false;
	}

	bool WindowsInput::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetRepeatCount() > 0) return false;

		m_PressedKey = e.GetKeyCode();
		m_IsKeyPressed = true;
		return false;
	}

	bool WindowsInput::OnKeyReleased(KeyReleasedEvent& e)
	{
		m_ReleasedKey = e.GetKeyCode();
		m_IsKeyReleased = true;
		return false;
	}

	bool WindowsInput::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		m_PressedButton = e.GetMouseButton();
		m_IsButtonPressed = true;
		return false;
	}

	bool WindowsInput::OnMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		m_ReleasedButton = e.GetMouseButton();
		m_IsButtonReleased = true;
		return false;
	}
}