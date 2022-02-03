#include "pch.h"
#include "Alpha/Manager/EventManager.h"

namespace Alpha
{
	EventManager* EventManager::s_Instance = nullptr;

	void EventManager::Init()
	{
		if (s_Instance != nullptr) return;
		s_Instance = new EventManager();
	}

	void EventManager::Shutdown()
	{
		if (s_Instance == nullptr) return;
		delete s_Instance;
		s_Instance = nullptr;
	}

	void EventManager::Submit(Event* e)
	{
		s_Instance->m_EventQueue.push(e);
	}

	void EventManager::Flush()
	{
		auto& callback = s_Instance->m_EventCallback;
		if (callback == nullptr) return;

		auto& queue = s_Instance->m_EventQueue;
		while (queue.size() > 0)
		{
			const auto& e = queue.front();
			queue.pop();

			callback(*e);

			delete e;
		}
	}
}