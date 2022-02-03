#include "pch.h"
#include "Alpha/Platform/WindowsWindow.h"

#include <GLFW/glfw3.h>

#include "Alpha/Event/ApplicationEvent.h"
#include "Alpha/Graphics/GraphicsContext.h"

namespace Alpha
{
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	void Window::Destroy(Window*& win)
	{
		if (win == nullptr) return;
		delete win;
		win = nullptr;
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.Title = props.Title;

		Init();
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init()
	{
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		if (!m_Window)
		{
			AP_ERROR("Failed to create window.");
			return;
		}
		AP_INFO("Window ({}, {}, \"{}\") created", m_Data.Width, m_Data.Height, m_Data.Title);

		m_Context = GraphicsContext::Create(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		InitCallbacks();
	}

	void WindowsWindow::InitCallbacks()
	{
		glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* win, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);
			data.Width = width;
			data.Height = height;

			if (data.EventCallback)
			{
				WindowResizeEvent* e = new WindowResizeEvent(width, height);
				data.EventCallback(e);
			}
			else
			{
				AP_ERROR("Unable to raise event (WindowResizeEvent). Do you forget to set event callback?");
			}
		});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* win)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(win);

			if (data.EventCallback)
			{
				WindowCloseEvent* e = new WindowCloseEvent();
				data.EventCallback(e);
			}
			else
			{
				AP_ERROR("Unable to raise event (WindowCloseEvent). Do you forget to set event callback?");
			}
		});
	}

	void WindowsWindow::Shutdown()
	{
		GraphicsContext::Destroy(m_Context);
		glfwDestroyWindow(m_Window);

		AP_INFO("Window : {} destroyed", m_Data.Title);
	}

	void WindowsWindow::OnUpdate()
	{
		m_Context->SwapBuffers();
		glfwPollEvents();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		m_Data.VSync = enabled;
		glfwSwapInterval(enabled ? 1 : 0);
	}
}