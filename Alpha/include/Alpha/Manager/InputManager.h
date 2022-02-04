#pragma once

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <functional>
#include "Alpha/Event/Event.h"

namespace Alpha
{
	class InputManager
	{
	public:
		using EventCallbackFunc = std::function<void(Event*)>;

		InputManager() = default;
		~InputManager() = default;

		static void Init(void* context);
		static void Shutdown();

		static void OnEvent(Event& event);
		static void PollEvents();

		inline static void SetEventCallback(EventCallbackFunc callback) { s_Instance->m_Callback = callback; }

	private:
		EventCallbackFunc m_Callback;
		static InputManager* s_Instance;

		static void InitCallbacks(void* context);
	};
}

#endif // !INPUTMANAGER_H
