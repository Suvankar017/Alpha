#include "pch.h"
#include "Alpha/Core/Engine.h"

#include "Alpha/Core/App.h"

#include "Alpha/Manager/LogManager.h"

namespace Alpha::Core
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
		Manager::LogManager::Init();

		m_App = CreateApp();
	}

	void Engine::Run()
	{
		m_App->OnUpdate();

		while (!m_IsRunning)
		{

		}
	}

	void Engine::Stop()
	{
		m_IsRunning = false;
	}

	void Engine::Shutdown()
	{
		DestroyApp(m_App);

		Manager::LogManager::Shutdown();
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