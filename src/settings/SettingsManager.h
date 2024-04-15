#ifndef SettingsManager_H
#define SettingsManager_H

#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include "mINI/ini.h"
#include <iostream>
#include "glad/glad.h"

class SettingsManager
{
private:
    // Window Settings
    int width = 800;
    int height = 600;
    const char *title = "Titanium Chess";
    GLFWmonitor *monitor = nullptr;
    int refreshRate = 60;

    // Resolution + HZ
    struct ScreenResolution
    {
        int width;
        int height;
        int hz;
    };

    // Display
    struct Monitor
    {
        std::vector<ScreenResolution> resolutions;
        std::string monitor_name;
    };

    // Monitor
    std::vector<Monitor> monitors;

    // Fullscreen
    bool fullscreen = 0;

    // VSync
    bool vSync = 1;

    // SELECTED OPTIONS
    int currentSelectedMonitor = 0;
    // ScreenResolution currentSelectedResolution = {0, 0, 0};

    // Save Default Settings File
    void SaveDefaultSettingsFile(const std::string &filename)
    {
        // Check if the directory exists
        std::filesystem::path documentsDir = std::filesystem::path(getenv("HOME")) / "Documents";
        if (!std::filesystem::exists(documentsDir))
        {
            std::cerr << "Directorul \"Documente\" nu există!" << std::endl;
            return;
        }

        // Check if the directory exists
        std::filesystem::path gameDir = documentsDir / "My Games" / "TitaniumChess";
        if (!std::filesystem::exists(gameDir))
        {
            std::filesystem::create_directories(gameDir);
        }

        // Check if the file already exists
        std::filesystem::path filePath = gameDir / filename;
        // if (std::filesystem::exists(filePath))
        // {
        //     std::cerr << "Fișierul " << filePath << " există deja. Nu se poate crea din nou." << std::endl;
        //     return;
        // }

        // Write the default settings to the file
        std::ofstream file(filePath);
        if (file.is_open())
        {
            ScreenResolution resolution = getDefaultDisplayResolution();

            file << "[Display]\n";
            file << "resolutionWidth = " + std::to_string(resolution.width) + "\n";
            file << "resolutionHeight = " + std::to_string(resolution.height) + "\n";
            file << "refreshRate = " + std::to_string(resolution.hz) + "\n";
            file << "fullscreen = " + std::to_string(fullscreen) + "\n";
            file << "vSync = " + std::to_string(vSync) + "\n";
            file.close();

            std::cout << "Setările implicite au fost salvate în fișier: " << filePath << std::endl;
        }
        else
        {
            std::cerr << "Eroare: Nu s-a putut deschide fișierul pentru scriere: " << filePath << std::endl;
        }
    }

    // TODO: Load Settings File
    void LoadSettingsFile(const std::string &filename)
    {
    }

public:
    // Constructor
    SettingsManager();

    // Destructor
    ~SettingsManager();

    // GET Width
    int getWidth()
    {
        return width;
    }
    // GET Height
    int getHeight()
    {
        return height;
    }
    // GET Title
    const char *getTitle()
    {
        return title;
    }
    // GET VSync
    bool getVSync()
    {
        return vSync;
    }
    // GET Fullscreen
    bool getFullscreen()
    {
        return fullscreen;
    }
    // GET Monitor
    GLFWmonitor *getMonitor()
    {
        return monitor;
    }
    // GET Refresh Rate
    int getRefreshRate()
    {
        return refreshRate;
    }

    // GET Default Monitors with Resolutions
    std::vector<Monitor> getDefaultMonitorsWithResolution()
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
    };

    ScreenResolution getDefaultDisplayResolution()
    {
        int index = monitors[currentSelectedMonitor].resolutions.size() - 1;
        return monitors[currentSelectedMonitor].resolutions[index];
    }
};

#endif // SETTINGSMANAGER_H