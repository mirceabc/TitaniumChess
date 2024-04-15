#include "WindowManager.h"

// Constructor
WindowManager::WindowManager(SettingsManager &settingsMgr) : settingsManager(settingsMgr){
    window = nullptr;
}

// Destructor
WindowManager::~WindowManager()
{
    if (window)
        glfwDestroyWindow(window);
    glfwTerminate();
}