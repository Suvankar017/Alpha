#pragma once

#ifndef OPENGLGRAPHICSCONTEXT_H
#define OPENGLGRAPHICSCONTEXT_H

#include "Alpha/Graphics/GraphicsContext.h"

struct GLFWwindow;

namespace Alpha
{
	class OpenGLGraphicsContext : public GraphicsContext
	{
	public:
		OpenGLGraphicsContext(GLFWwindow* window);

		virtual void SwapBuffers() override;

	private:
		GLFWwindow* m_Window;
	};
}

#endif // !OPENGLGRAPHICSCONTEXT_H
