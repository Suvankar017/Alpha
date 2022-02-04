#pragma once

#ifndef WINDOWSINPUT_H
#define WINDOWSINPUT_H

#include "Alpha/Input/Input.h"
#include "Alpha/Event/KeyEvent.h"
#include "Alpha/Event/MouseEvent.h"

namespace Alpha
{
	class WindowsInput : public Input
	{
	public:
		WindowsInput();

	protected:
		virtual ~WindowsInput();

		virtual std::pair<float, float> GetMousePosition() override;
		virtual std::pair<float, float> GetMouseScrollDelta() override;

		virtual bool GetKey(int key) override;
		virtual bool GetKeyDown(int key) override;
		virtual bool GetKeyUp(int key) override;
		virtual bool GetMouseButton(int button) override;
		virtual bool GetMouseButtonDown(int button) override;
		virtual bool GetMouseButtonUp(int button) override;

		virtual void OnEvent(Event& event) override;
		virtual void OnReset() override;

	private:
		float m_XOffset, m_YOffset;
		int m_PressedKey, m_ReleasedKey;
		int m_PressedButton, m_ReleasedButton;
		bool m_IsKeyPressed, m_IsKeyReleased;
		bool m_IsButtonPressed, m_IsButtonReleased;

		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyReleased(KeyReleasedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& e);
	};
}

#endif // !WINDOWSINPUT_H
