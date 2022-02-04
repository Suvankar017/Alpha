#pragma once

#ifndef KEYEVENT_H
#define KEYEVENT_H

#include <sstream>

#include "Alpha/Event/Event.h"

namespace Alpha
{
	class KeyEvent : public Event
	{
	protected:
		int m_KeyCode;
		KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY((int)EventCategory::Keyboard | (int)EventCategory::Input)
	};

	class KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;

	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent : " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public Event
	{
	private:
		char m_Character;

	public:
		KeyTypedEvent(char character) : m_Character(character) {}

		inline char GetCharacter() const { return m_Character; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent : " << m_Character;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
		EVENT_CLASS_CATEGORY((int)EventCategory::Keyboard | (int)EventCategory::Input)
	};
}

#endif // !KEYEVENT_H
