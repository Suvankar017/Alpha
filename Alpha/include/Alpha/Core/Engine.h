#pragma once

#ifndef ENGINE_H
#define ENGINE_H

namespace Alpha
{
	class Window;
	class App;
	class Event;
	class WindowCloseEvent;

	class Engine
	{
	public:
		~Engine();

		void Run();
		void Stop();

		inline static Engine& Get() { return*s_Instance; }

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

		bool OnWindowClose(WindowCloseEvent& event);
	};
}

#endif // !ENGINE_H
