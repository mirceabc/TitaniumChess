#include "SettingsManager.h"

// Constructor
SettingsManager::SettingsManager()
{
    getAllMonitorsWithResolutions();
    LoadSettingsFromFile("settings.ini");
}

// Destructor
SettingsManager::~SettingsManager() {

}

// Get Default Monitor Resolution
SettingsManager::ScreenResolution SettingsManager::getDefaultDisplayResolution()
{
    int index = monitors[currentSelectedMonitor].resolutions.size() - 1;
    return monitors[currentSelectedMonitor].resolutions[index];
}

// GET All Monitors with Resolutions
std::vector<SettingsManager::Monitor> SettingsManager::getAllMonitorsWithResolutions()
{
    int count;
    GLFWmonitor **display = glfwGetMonitors(&count);

    for (int i = 0; i < count; i++)
    {
        Monitor monitor;
        monitor.monitor_name = glfwGetMonitorName(display[i]);

        int modeCount;
        const GLFWvidmode *modes = glfwGetVideoModes(display[i], &modeCount);
        for (int j = 0; j < modeCount; j++)
        {
            if ((modes[j].refreshRate == 144) || (modes[j].refreshRate == 120) || (modes[j].refreshRate == 60))
            {
                monitor.resolutions.push_back({modes[j].width, modes[j].height, modes[j].refreshRate});
            }
        }
        monitors.push_back(monitor);
    }

    // DEBUG - Print monitors
    // for(int i = 0; i < monitors.size(); i++)
    // {
    //     std::cout << "Monitor: " << monitors[i].monitor_name << std::endl;
    //     for(int j = 0; j < monitors[i].resolutions.size(); j++)
    //     {
    //         std::cout << "Resolution: " << monitors[i].resolutions[j].width << "x" << monitors[i].resolutions[j].height << " @ " << monitors[i].resolutions[j].hz << "Hz" << std::endl;
    //     }
    // }

    return monitors;
}