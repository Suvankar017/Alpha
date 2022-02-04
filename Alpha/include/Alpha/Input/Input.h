#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "Alpha/Input/KeyCode.h"

namespace Alpha
{
	class Event;

	class Input
	{
	public:
		inline static std::pair<float, float> MousePosition() { return s_Instance->GetMousePosition(); }
		inline static std::pair<float, float> MouseScrollDelta() { return s_Instance->GetMouseScrollDelta(); }

		inline static bool GetKey(KeyCode key) { return s_Instance->GetKey((int)key); }
		inline static bool GetKeyDown(KeyCode key) { return s_Instance->GetKeyDown((int)key); }
		inline static bool GetKeyUp(KeyCode key) { return s_Instance->GetKeyUp((int)key); }
		inline static bool GetMouseButton(MouseButton button) { return s_Instance->GetMouseButton((int)button); }
		inline static bool GetMouseButtonDown(MouseButton button) { return s_Instance->GetMouseButtonDown((int)button); }
		inline static bool GetMouseButtonUp(MouseButton button) { return s_Instance->GetMouseButtonUp((int)button); }

	protected:
		virtual ~Input() {}

		virtual std::pair<float, float> GetMousePosition() = 0;
		virtual std::pair<float, float> GetMouseScrollDelta() = 0;

		virtual bool GetKey(int key) = 0;
		virtual bool GetKeyDown(int key) = 0;
		virtual bool GetKeyUp(int key) = 0;
		virtual bool GetMouseButton(int button) = 0;
		virtual bool GetMouseButtonDown(int button) = 0;
		virtual bool GetMouseButtonUp(int button) = 0;

		virtual void OnEvent(Event& event) = 0;
		virtual void OnReset() {}

	private:
		static Input* s_Instance;
		friend class InputManager;
	};
}

#endif // !INPUT_H
