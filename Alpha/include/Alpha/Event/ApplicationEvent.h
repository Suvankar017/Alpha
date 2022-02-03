#pragma once

#ifndef APPLICATIONEVENT_H
#define APPLICATIONEVENT_H

#include <sstream>

#include "Alpha/Event/Event.h"

namespace Alpha
{
	class WindowResizeEvent : public Event
	{
	private:
		unsigned int m_Width, m_Height;

	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent : (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY((int)EventCategory::Application)
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY((int)EventCategory::Application)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY((int)EventCategory::Application)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY((int)EventCategory::Application)
	};

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY((int)EventCategory::Application)
	};
}

#endif // !APPLICATIONEVENT_H
