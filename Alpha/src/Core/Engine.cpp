#include "pch.h"
#include "Alpha/Core/Engine.h"

#include "Alpha/Macros.h"
#include "Alpha/Manager/LogManager.h"
#include "Alpha/Manager/EventManager.h"
#include "Alpha/Manager/InputManager.h"

#include "Alpha/Input/Input.h"

#include "../External/GLFW.h"

namespace Alpha
{
	Engine* Engine::s_Instance = nullptr;

	Engine::Engine()
	{
		s_Instance = this;
		m_IsRunning = true;
		m_App = nullptr;

		Init();
	}

	Engine::~Engine()
	{
		Shutdown();
	}

	void Engine::Init()
	{
		LogManager::Init();

		EventManager::Init();
		EventManager::SetEventCallback(BIND_EVENT_FUNC(Engine::OnEvent));

		GLFW::Init();

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Engine::PullEvent));

		InputManager::Init(m_Window->GetNativeWindow());
		InputManager::SetEventCallback(BIND_EVENT_FUNC(Engine::PullEvent));

		m_App = CreateApp();
	}

	void Engine::Shutdown()
	{
		DestroyApp(m_App);

		InputManager::Shutdown();
		Window::Destroy(m_Window);
		GLFW::Shutdown();
		EventManager::Shutdown();
		LogManager::Shutdown();
	}

	void Engine::PullEvent(Event* event)
	{
		EventManager::Submit(event);
	}

	void Engine::OnEvent(Event& event)
	{
		InputManager::OnEvent(event);

		EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FUNC(Engine::OnWindowResize));
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Engine::OnWindowClose));
		//dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNC(Engine::OnKeyPressed));
		//dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNC(Engine::OnKeyReleased));
		//dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNC(Engine::OnKeyTyped));
		//dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNC(Engine::OnMouseMoved));
		//dispatcher.Dispatch<MouseEnterEvent>(BIND_EVENT_FUNC(Engine::OnMouseEnter));
		//dispatcher.Dispatch<MouseExitEvent>(BIND_EVENT_FUNC(Engine::OnMouseExit));
		//dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNC(Engine::OnMouseScrolled));
		//dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNC(Engine::OnMouseButtonPressed));
		//dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNC(Engine::OnMouseButtonReleased));
	}

	bool Engine::OnWindowResize(WindowResizeEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnWindowClose(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		return false;
	}

	bool Engine::OnKeyPressed(KeyPressedEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnKeyReleased(KeyReleasedEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnKeyTyped(KeyTypedEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnMouseMoved(MouseMovedEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnMouseEnter(MouseEnterEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnMouseExit(MouseExitEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnMouseScrolled(MouseScrolledEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnMouseButtonPressed(MouseButtonPressedEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	bool Engine::OnMouseButtonReleased(MouseButtonReleasedEvent& event)
	{
		AP_TRACE(event);
		return false;
	}

	void Engine::Run()
	{
		while (m_IsRunning)
		{
			EventManager::Flush();

			m_App->OnUpdate();
			m_Window->OnUpdate();

			InputManager::PollEvents();
		}
	}

	void Engine::Stop()
	{
		m_IsRunning = false;
	}

	Engine* Engine::Create()
	{
		return (s_Instance != nullptr) ? nullptr : new Engine();
	}

	void Engine::Destory(Engine*& engine)
	{
		if (engine == nullptr) return;
		delete engine;
		engine = nullptr;
	}
}