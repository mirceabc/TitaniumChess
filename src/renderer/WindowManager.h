#ifndef WindowManager_H
#define WindowManager_H

#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../settings/SettingsManager.h"

class WindowManager
{
private:
    GLFWwindow *window;
    SettingsManager &settingsManager;

    int width = settingsManager.getWidth();
    int height = settingsManager.getHeight();
    const char *title = settingsManager.getTitle();
    bool vSync = settingsManager.getVSync();
    bool fullscreen = settingsManager.getFullscreen();
    GLFWmonitor *monitor = settingsManager.getMonitor();
    int refreshRate = settingsManager.getRefreshRate();

public:
    WindowManager(SettingsManager &settingsMgr);
    ~WindowManager();

    GLFWwindow *createGLFWWindow()
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

#ifdef __APPLE__ // For MacOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

        if(fullscreen)
        {
            const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
            width = mode->width;
            height = mode->height;

            window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), nullptr);
        }
        else{
            window = glfwCreateWindow(width, height, title, monitor, nullptr);
        }
        
        if (!window)
        {
            std::cerr << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return nullptr;
        }

        glfwMakeContextCurrent(window);

        if(vSync)
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize GLAD" << std::endl;
            return nullptr;
        }

        glViewport(0, 0, width, height);

        return window;
    }

    GLFWwindow *getWindow() const
    {
        return window;
    }
};

#endif // WindowManager_H