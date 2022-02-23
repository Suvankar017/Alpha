#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <functional>
#include <spdlog/fmt/ostr.h>

#define BIT(x) (1 << x)
#define EVENT_CLASS_TYPE(type)	static Alpha::EventType GetStaticType() { return EventType::##type; }\
								virtual Alpha::EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

namespace Alpha
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled, MouseEnter, MouseExit
	};

	enum class EventCategory
	{
		None = 0,
		Application = BIT(0),
		Input = BIT(1),
		Keyboard = BIT(2),
		Mouse = BIT(3),
		MouseButton = BIT(4)
	};

	class Event
	{
	private:
		friend class EventDispatcher;

	protected:
		bool m_Handled = false;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }
		virtual bool IsHandled() const { return m_Handled; }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & (int)category; }

		friend std::ostream& operator<<(std::ostream& os, const Event& e)
		{
			return os << e.ToString();
		}
	};

	class EventDispatcher
	{
	private:
		Event& m_Event;
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	};
}

#endif // !EVENT_H
