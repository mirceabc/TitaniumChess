#include "Core.h"

Core::Core()
{
   init();
}

Core::~Core()
{
    destroy();
}

int Core::init()
{
    if(!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }
}

void Core::run(GLFWwindow* window, InputManager &inputManager)
{
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        inputManager.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        glfwSwapBuffers(window);
    }
}

void Core::destroy()
{
    glfwTerminate();
}