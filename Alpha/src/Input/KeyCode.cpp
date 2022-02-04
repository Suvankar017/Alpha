#include "pch.h"
#include "Alpha/Input/KeyCode.h"

#include <spdlog/fmt/ostr.h>

namespace Alpha
{
	std::ostream& operator<<(std::ostream& os, const KeyCode& key)
	{
		return os << "KeyCode : " << GetKeyCodeName(key);
	}

	std::ostream& operator<<(std::ostream& os, const MouseButton& button)
	{
		return os << "MouseButton : " << GetMouseButtonName(button);
	}

	int operator ~(KeyCode key) { return (int)key; }

	int operator ~(MouseButton button) { return (int)button; }

	const char* GetKeyCodeName(KeyCode key)
	{
		switch (key)
		{
			case Alpha::KeyCode::Unknown: return "Unknown";
			case Alpha::KeyCode::Space: return "Space";
			case Alpha::KeyCode::Apostrophe: return "Apostrophe";
			case Alpha::KeyCode::Comma: return "Comma";
			case Alpha::KeyCode::Minus: return "Minus";
			case Alpha::KeyCode::Period: return "Period";
			case Alpha::KeyCode::Slash: return "Slash";
			case Alpha::KeyCode::Alpha0: return "Alpha0";
			case Alpha::KeyCode::Alpha1: return "Alpha1";
			case Alpha::KeyCode::Alpha2: return "Alpha2";
			case Alpha::KeyCode::Alpha3: return "Alpha3";
			case Alpha::KeyCode::Alpha4: return "Alpha4";
			case Alpha::KeyCode::Alpha5: return "Alpha5";
			case Alpha::KeyCode::Alpha6: return "Alpha6";
			case Alpha::KeyCode::Alpha7: return "Alpha7";
			case Alpha::KeyCode::Alpha8: return "Alpha8";
			case Alpha::KeyCode::Alpha9: return "Alpha9";
			case Alpha::KeyCode::SemiColon: return "SemiColon";
			case Alpha::KeyCode::Equal: return "Equal";
			case Alpha::KeyCode::A: return "A";
			case Alpha::KeyCode::B: return "B";
			case Alpha::KeyCode::C: return "C";
			case Alpha::KeyCode::D: return "D";
			case Alpha::KeyCode::E: return "E";
			case Alpha::KeyCode::F: return "F";
			case Alpha::KeyCode::G: return "G";
			case Alpha::KeyCode::H: return "H";
			case Alpha::KeyCode::I: return "I";
			case Alpha::KeyCode::J: return "J";
			case Alpha::KeyCode::K: return "K";
			case Alpha::KeyCode::L: return "L";
			case Alpha::KeyCode::M: return "M";
			case Alpha::KeyCode::N: return "N";
			case Alpha::KeyCode::O: return "O";
			case Alpha::KeyCode::P: return "P";
			case Alpha::KeyCode::Q: return "Q";
			case Alpha::KeyCode::R: return "R";
			case Alpha::KeyCode::S: return "S";
			case Alpha::KeyCode::T: return "T";
			case Alpha::KeyCode::U: return "U";
			case Alpha::KeyCode::V: return "V";
			case Alpha::KeyCode::W: return "W";
			case Alpha::KeyCode::X: return "X";
			case Alpha::KeyCode::Y: return "Y";
			case Alpha::KeyCode::Z: return "Z";
			case Alpha::KeyCode::LeftBracket: return "LeftBracket";
			case Alpha::KeyCode::BackSlash: return "BackSlash";
			case Alpha::KeyCode::RightBracket: return "RightBracket";
			case Alpha::KeyCode::GraveAccent: return "GraveAccent";
			case Alpha::KeyCode::World1: return "World1";
			case Alpha::KeyCode::World2: return "World2";
			case Alpha::KeyCode::Escape: return "Escape";
			case Alpha::KeyCode::Enter: return "Enter";
			case Alpha::KeyCode::Tab: return "Tab";
			case Alpha::KeyCode::Backspace: return "Backspace";
			case Alpha::KeyCode::Insert: return "Insert";
			case Alpha::KeyCode::Delete: return "Delete";
			case Alpha::KeyCode::Right: return "Right";
			case Alpha::KeyCode::Left: return "Left";
			case Alpha::KeyCode::Down: return "Down";
			case Alpha::KeyCode::Up: return "Up";
			case Alpha::KeyCode::PageUp: return "PageUp";
			case Alpha::KeyCode::PageDown: return "PageDown";
			case Alpha::KeyCode::Home: return "Home";
			case Alpha::KeyCode::End: return "End";
			case Alpha::KeyCode::CapsLock: return "CapsLock";
			case Alpha::KeyCode::ScrollLock: return "ScrollLock";
			case Alpha::KeyCode::NumLock: return "NumLock";
			case Alpha::KeyCode::PrintScreen: return "PrintScreen";
			case Alpha::KeyCode::Pause: return "Pause";
			case Alpha::KeyCode::F1: return "F1";
			case Alpha::KeyCode::F2: return "F2";
			case Alpha::KeyCode::F3: return "F3";
			case Alpha::KeyCode::F4: return "F4";			
			case Alpha::KeyCode::F5: return "F5";			
			case Alpha::KeyCode::F6: return "F6";			
			case Alpha::KeyCode::F7: return "F7";			
			case Alpha::KeyCode::F8: return "F8";			
			case Alpha::KeyCode::F9: return "F9";			
			case Alpha::KeyCode::F10: return "F10";			
			case Alpha::KeyCode::F11: return "F11";			
			case Alpha::KeyCode::F12: return "F12";			
			case Alpha::KeyCode::F13: return "F13";			
			case Alpha::KeyCode::F14: return "F14";			
			case Alpha::KeyCode::F15: return "F15";			
			case Alpha::KeyCode::F16: return "F16";			
			case Alpha::KeyCode::F17: return "F17";			
			case Alpha::KeyCode::F18: return "F18";			
			case Alpha::KeyCode::F19: return "F19";			
			case Alpha::KeyCode::F20: return "F20";			
			case Alpha::KeyCode::F21: return "F21";			
			case Alpha::KeyCode::F22: return "F22";			
			case Alpha::KeyCode::F23: return "F23";			
			case Alpha::KeyCode::F24: return "F24";			
			case Alpha::KeyCode::F25: return "F25";			
			case Alpha::KeyCode::Keypad0: return "Keypad0";			
			case Alpha::KeyCode::Keypad1: return "Keypad1";			
			case Alpha::KeyCode::Keypad2: return "Keypad2";			
			case Alpha::KeyCode::Keypad3: return "Keypad3";			
			case Alpha::KeyCode::Keypad4: return "Keypad4";			
			case Alpha::KeyCode::Keypad5: return "Keypad5";			
			case Alpha::KeyCode::Keypad6: return "Keypad6";			
			case Alpha::KeyCode::Keypad7: return "Keypad7";			
			case Alpha::KeyCode::Keypad8: return "Keypad8";			
			case Alpha::KeyCode::Keypad9: return "Keypad9";			
			case Alpha::KeyCode::KeypadDecimal: return "KeypadDecimal";			
			case Alpha::KeyCode::KeypadDivide: return "KeypadDivide";			
			case Alpha::KeyCode::KeypadMultiply: return "KeypadMultiply";			
			case Alpha::KeyCode::KeypadSubtrack: return "KeypadSubtrack";			
			case Alpha::KeyCode::KeypadAdd: return "KeypadAdd";			
			case Alpha::KeyCode::KeypadEnter: return "KeypadEnter";
			case Alpha::KeyCode::KeypadEqual: return "KeypadEqual";
			case Alpha::KeyCode::LeftShift:return "LeftShift";
			case Alpha::KeyCode::LeftCtrl: return "LeftCtrl";
			case Alpha::KeyCode::LeftAlt: return "LeftAlt";
			case Alpha::KeyCode::LeftSuper: return "LeftSuper";
			case Alpha::KeyCode::RightShift: return "RightShift";
			case Alpha::KeyCode::RightCtrl: return "RightCtrl";
			case Alpha::KeyCode::RightAlt: return "RightAlt";
			case Alpha::KeyCode::RightSuper: return "RightSuper";
			case Alpha::KeyCode::Menu: return "Menu";
		}
		return "Unknown";
	}

	const char* GetMouseButtonName(MouseButton button)
	{
		switch (button)
		{
			case Alpha::MouseButton::Unknown: return "Unknown";
			case Alpha::MouseButton::Mouse1: return "Mouse1 | MouseLeft";
			case Alpha::MouseButton::Mouse2: return "Mouse2 | MouseRight";
			case Alpha::MouseButton::Mouse3: return "Mouse3 | MouseMiddle";
			case Alpha::MouseButton::Mouse4: return "Mouse4";
			case Alpha::MouseButton::Mouse5: return "Mouse5";
			case Alpha::MouseButton::Mouse6: return "Mouse6";
			case Alpha::MouseButton::Mouse7: return "Mouse7";
			case Alpha::MouseButton::Mouse8: return "Mouse8";
		}
		return "Unknown";
	}

	KeyCode GetKeyCode(int keyCode)
	{
		return (KeyCode)keyCode;
	}

	MouseButton GetMouseButton(int mouseButton)
	{
		return (MouseButton)mouseButton;
	}

}