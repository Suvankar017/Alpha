#include "pch.h"
#include "Alpha/Core/Engine.h"

#include "Alpha/Macros.h"
#include "Alpha/Core/App.h"
#include "Alpha/Core/Window.h"
#include "Alpha/Event/Event.h"
#include "Alpha/Event/ApplicationEvent.h"
#include "Alpha/Manager/LogManager.h"
#include "Alpha/Manager/EventManager.h"

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
		GLFW::Init();

		EventManager::SetEventCallback(BIND_EVENT_FUNC(Engine::OnEvent));
		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FUNC(Engine::PullEvent));

		m_App = CreateApp();
	}

	void Engine::Shutdown()
	{
		DestroyApp(m_App);

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
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(Engine::OnWindowClose));
	}

	bool Engine::OnWindowClose(WindowCloseEvent& event)
	{
		m_IsRunning = false;
		return false;
	}

	void Engine::Run()
	{
		while (m_IsRunning)
		{
			EventManager::Flush();

			m_App->OnUpdate();
			m_Window->OnUpdate();
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