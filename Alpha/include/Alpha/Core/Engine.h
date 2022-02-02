#pragma once

#ifndef ENGINE_H
#define ENGINE_H

namespace Alpha::Core
{
	class App;

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

		App* m_App;

		static Engine* s_Instance;

		Engine();

		void Init();
		void Shutdown();
	};
}

#endif // !ENGINE_H
