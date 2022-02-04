#pragma once

#ifndef MOUSEEVENT_H
#define MOUSEEVENT_H

#include <sstream>

#include "Alpha/Event/Event.h"

namespace Alpha
{
	class MouseMovedEvent : public Event
	{
	private:
		float m_MouseX, m_MouseY;

	public:
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent : (" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)
	};

	class MouseEnterEvent : public Event
	{
	public:
		MouseEnterEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseEnterEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseEnter)
		EVENT_CLASS_CATEGORY((int)EventCategory::Mouse)
	};

	class MouseExitEvent : public Event
	{
	public:
		MouseExitEvent() {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseExitEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseExit)
		EVENT_CLASS_CATEGORY((int)EventCategory::Mouse)
	};

	class MouseScrolledEvent : public Event
	{
	private:
		float m_XOffset, m_YOffset;

	public:
		MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent : (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)
	};

	class MouseButtonEvent : public Event
	{
	protected:
		int m_Button;

		MouseButtonEvent(int button) : m_Button(button) {}

	public:
		inline int GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent : " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent : " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}

#endif // !MOUSEEVENT_H
