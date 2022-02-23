#pragma once

#ifndef ENGINE_H
#define ENGINE_H

#include "Alpha/Core/Window.h"
#include "Alpha/Event/Event.h"
#include "Alpha/Event/ApplicationEvent.h"
#include "Alpha/Event/KeyEvent.h"
#include "Alpha/Event/MouseEvent.h"

namespace Alpha
{
	class App;

	class Engine
	{
	public:
		~Engine();

		void Run();
		void Stop();

		inline Window& GetWindow() { return *m_Window; }
		inline static Engine& Get() { return *s_Instance; }

		static Engine* Create();
		static void Destory(Engine*& engine);

	private:
		bool m_IsRunning;
		Window* m_Window;
		App* m_App;
		static Engine* s_Instance;

		Engine();

		void Init();
		void Shutdown();
		void PullEvent(Event* event);
		void OnEvent(Event& event);

		bool OnWindowResize(WindowResizeEvent& event);
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseEnter(MouseEnterEvent& event);
		bool OnMouseExit(MouseExitEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
	};
}

#endif // !ENGINE_H
