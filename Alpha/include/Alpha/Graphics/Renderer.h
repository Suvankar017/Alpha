#pragma once

#include <queue>

#include "Alpha/Graphics/RenderCommand.h"

namespace Alpha
{
	class Renderer
	{
	public:
		static void Submit(const RenderCommandTemp& command);

	private:
		static std::queue<RenderCommandTemp> m_CommandsQueue;

		static void Init();
		static void Flush();
		static void Shutdown();

		friend class Engine;
	};
}