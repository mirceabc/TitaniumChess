#ifndef Core_H
#define Core_H

#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../input/InputManager.h"

class Core
{
private:
    int init();
    void destroy();

public:
    Core();
    ~Core();
    void run(GLFWwindow *window, InputManager &inputManager);
};

#endif // Core_H