#include "engine.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace Alpha
{
    void PrintConfig()
    {
#if ALPHA_PLATFORM_WINDOWS
        std::cout << "Platform : Windows" << std::endl;
#elif ALPHA_PLATFORM_MAC
        std::cout << "Platform : Mac" << std::endl;
#elif ALPHA_PLATFORM_LINUX
        std::cout << "Platform : Linux" << std::endl;
#endif
#if ALPHA_DEBUG
        std::cout << "Configuration : Debug" << std::endl;
#elif ALPHA_RELEASE
        std::cout << "Configuration : Release" << std::endl;
#endif
    }

	void Run()
	{
        /* Initialize the library */
        if (!glfwInit())
            return;

        /* Create a windowed mode window and its OpenGL context */
        GLFWwindow* window = glfwCreateWindow(640, 480, "Alpha Window", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
	}
}