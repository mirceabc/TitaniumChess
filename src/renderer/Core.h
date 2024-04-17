#ifndef Core_H
#define Core_H

#include "../utilities/CommonIncludes.h"
#include "../input/InputManager.h"
#include "../shaders/shaders.h"
#include "../entities/VBO.h"
#include "../entities/VAO.h"
#include "../entities/EBO.h"

// IMGUI
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
// ----------------------------

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