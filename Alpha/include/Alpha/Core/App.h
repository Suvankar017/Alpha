#pragma once

#ifndef APP_H
#define APP_H

#include "Alpha/Event/Event.h"
#include "Alpha/Core/Engine.h"
#include "Alpha/Graphics/Shader.h"
#include "Alpha/Graphics/VertexArray.h"

namespace Alpha
{
	class App
	{
	public:
		App();
		virtual ~App();

		virtual void OnEvent(Event& e);
		virtual void OnUpdate();

		inline void Close() const { Engine::Get().Stop(); }

	private:
		//uint32_t m_VAO;
		//uint32_t m_VBO;
		//uint32_t m_EBO;
		//Shader m_Shader;
	};

	App* CreateApp();
	void DestroyApp(App*& app);
}

#endif // !APP_H
