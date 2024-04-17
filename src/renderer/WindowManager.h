#ifndef WindowManager_H
#define WindowManager_H

#include "../utilities/CommonIncludes.h"
#include "../settings/SettingsManager.h"

// IMGUI
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
// ----------------------------

class WindowManager
{
private:
    GLFWwindow *window = nullptr;
    SettingsManager &settingsManager;

    int width = settingsManager.getWidth();
    int height = settingsManager.getHeight();
    const char *title = settingsManager.getTitle();
    bool vSync = settingsManager.getVSync();
    bool fullscreen = settingsManager.getFullscreen();
    GLFWmonitor *monitor = settingsManager.getMonitor();
    int refreshRate = settingsManager.getRefreshRate();

    static void framebuffer_size_callback(GLFWwindow *window, int width, int height) { glViewport(0, 0, width, height); }

    GLFWwindow *createGLFWWindow()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

#ifdef __APPLE__ // For MacOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

        if (fullscreen)
        {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            width = mode->width;
            height = mode->height;

            window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
        }
        else
        {
            window = glfwCreateWindow(width, height, title, monitor, nullptr);
        }

        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);

        if (vSync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // TEST IMGUI INIT
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");
        // ----------------------------

        return window;
    }

public:
    WindowManager(SettingsManager &settingsMgr);
    ~WindowManager();

    GLFWwindow *getWindow() const { return window; }
};

#endif // WindowManager_H