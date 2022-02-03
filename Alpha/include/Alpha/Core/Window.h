#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <functional>

namespace Alpha
{
	class Event;

	struct WindowProps
	{
		unsigned int Width, Height;
		std::string Title;

		WindowProps(unsigned int width = 800, unsigned int height = 600, const std::string& title = "New Window") :
			Width(width), Height(height), Title(title) {}
	};

	class Window
	{
	public:
		using EventCallbackFunc = std::function<void(Event*)>;

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual bool IsVSync() const = 0;

		virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;

		static Window* Create(const WindowProps& props = WindowProps());
		static void Destroy(Window*& win);

	protected:
		virtual ~Window() {}
	};
}

#endif // !WINDOW_H
