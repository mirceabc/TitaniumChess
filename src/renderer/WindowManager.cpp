#include "WindowManager.h"

// Constructor
WindowManager::WindowManager(SettingsManager &settingsMgr) : settingsManager(settingsMgr){
    createGLFWWindow();
}

// Destructor
WindowManager::~WindowManager()
{
    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();
}