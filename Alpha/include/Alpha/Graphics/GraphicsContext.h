#pragma once

#ifndef GRAPHICSCONTEXT_H
#define GRAPHICSCONTEXT_H

namespace Alpha
{
	class GraphicsContext
	{
	public:
		virtual void SetCurrentContext(void* context) = 0;
		virtual void SwapBuffers() = 0;

		static GraphicsContext* Create(void* context);
		static void Destroy(GraphicsContext*& context);
	};
}

#endif // !GRAPHICSCONTEXT_H
