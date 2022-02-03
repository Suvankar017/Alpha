#pragma once

#ifndef GLFW_H
#define GLFW_H

namespace Alpha
{
	class GLFW
	{
	public:
		static void Init();
		static void Shutdown();

	private:
		static bool s_IsInitialized;
	};
}

#endif // !GLFW_H
