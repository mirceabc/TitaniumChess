#ifndef Core_H
#define Core_H

#include "../utilities/CommonIncludes.h"
#include "../utilities/fps_utils.h"
#include "../input/InputManager.h"
#include "../shaders/Shaders.h"
#include "../entities/rendering/VBO.h"
#include "../entities/rendering/VAO.h"
#include "../entities/rendering/EBO.h"
#include "../entities/camera/Camera.h"

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