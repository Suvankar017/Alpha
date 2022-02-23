#include "pch.h"
#include "Alpha/Graphics/Renderer.h"

#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Alpha
{
	std::queue<RenderCommandTemp> Renderer::m_CommandsQueue;

	void Renderer::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		stbi_set_flip_vertically_on_load(true);
	}

	void Renderer::Submit(const RenderCommandTemp& command)
	{
		m_CommandsQueue.push(command);
	}

	void Renderer::Flush()
	{
		glClearColor(0.33f, 0.541f, 0.167f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		while (m_CommandsQueue.size() > 0)
		{
			const auto& command = m_CommandsQueue.front();
			m_CommandsQueue.pop();

			auto c = command.lock();
			if (!c) continue;

			c->Execute();
		}
	}

	void Renderer::Shutdown()
	{

	}
}