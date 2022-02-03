#pragma once

#ifndef WINDOWSWINDOW_H
#define WINDOWSWINDOW_H

#include "Alpha/Core/Window.h"

struct GLFWwindow;

namespace Alpha
{
	class GraphicsContext;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual void OnUpdate() override;

		inline virtual unsigned int GetWidth() const override { return m_Data.Width; }
		inline virtual unsigned int GetHeight() const override { return m_Data.Height; }
		inline virtual void* GetNativeWindow() const override { return m_Window; }
		inline virtual bool IsVSync() const override { return m_Data.VSync; }

		inline virtual void SetEventCallback(const EventCallbackFunc& callback) override { m_Data.EventCallback = callback; }
		virtual void SetVSync(bool enabled) override;

	protected:
		virtual ~WindowsWindow();

	private:
		struct WindowData
		{
			unsigned int Width, Height;
			std::string Title;
			bool VSync;
			EventCallbackFunc EventCallback;

			WindowData()
			{
				Width = 640;
				Height = 480;
				Title = "Window";
				VSync = false;
				EventCallback = nullptr;
			}
		};

		WindowData m_Data;
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		void Init();
		void InitCallbacks();
		void Shutdown();
	};
}

#endif // !WINDOWSWINDOW_H
