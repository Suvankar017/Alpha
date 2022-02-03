#pragma once

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <queue>
#include "Alpha/Event/Event.h"

namespace Alpha
{
	class EventManager
	{
	public:
		using EventCallbackFunc = std::function<void(Event&)>;

		EventManager() = default;
		~EventManager() = default;

		static void Init();
		static void Shutdown();

		inline static void SetEventCallback(EventCallbackFunc callback) { s_Instance->m_EventCallback = callback; }

		static void Submit(Event* e);
		static void Flush();

	private:
		EventCallbackFunc m_EventCallback;
		std::queue<Event*> m_EventQueue;
		static EventManager* s_Instance;
	};
}

#endif // !EVENTMANAGER_H
