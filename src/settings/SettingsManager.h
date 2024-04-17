#ifndef SettingsManager_H
#define SettingsManager_H

#include "../utilities/CommonIncludes.h"
#include "mINI/ini.h"

#include <vector>

class SettingsManager
{
private:
    // Default Window Settings
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    int width = glfwGetVideoMode(monitor)->width;
    int height = glfwGetVideoMode(monitor)->height;
    const char *title = "Titanium Chess";
    int refreshRate = glfwGetVideoMode(monitor)->refreshRate;

    // Resolution and Refresh Rate
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
    bool fullscreen = 1;

    // VSync
    bool vSync = 1;

    // SELECTED OPTIONS
    int currentSelectedMonitor = 0;
    // ScreenResolution currentSelectedResolution = {0, 0, 0};

    // Save Default Settings to file settings.ini
    void SaveDefaultSettingsToFile(const std::string &filename, const std::string &filePath)
    {
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

    // Load Settings from file settings.ini
    void LoadSettingsFromFile(const std::string &filename)
    {
        // Check if the game settings directory exists
        std::filesystem::path gameDir = std::filesystem::path(getenv("HOME")) / "Documents" / "My Games" / "TitaniumChess";
        std::filesystem::path filePath = gameDir / filename;
        if (!std::filesystem::exists(gameDir))
        {
            std::filesystem::create_directories(gameDir);
            SaveDefaultSettingsToFile(filename, filePath);
            return;
        }

        // Check if the settings.ini file already exists
        if (std::filesystem::exists(filePath))
        {
            mINI::INIFile file(filePath);
            mINI::INIStructure ini;
            file.read(ini);

            CheckSettingsFromFile(file, ini);

            setWidth(std::stoi(ini["Display"]["resolutionWidth"]));
            setHeight(std::stoi(ini["Display"]["resolutionHeight"]));
            setRefreshRate(std::stoi(ini["Display"]["refreshRate"]));
            if ((std::stoi(ini["Display"]["fullscreen"])) == 1)
            {
                setMonitor(glfwGetPrimaryMonitor());
                setFullscreen(true);
            }
            else if ((std::stoi(ini["Display"]["fullscreen"])) == 0)
            {
                setMonitor(nullptr);
                setFullscreen(false);
            }
            setVSync(std::stoi(ini["Display"]["vSync"]));
        }
        else
        {
            SaveDefaultSettingsToFile(filename, filePath);
        }
    }

    // Check if the settings.ini file is valid and update it if necessary
    void CheckSettingsFromFile(mINI::INIFile &file, mINI::INIStructure &ini)
    {
        // TODO UPDATE: Check if is monitor supported resolutions in file
        if ((ini["Display"]["resolutionWidth"].empty()) || (std::stoi(ini["Display"]["resolutionWidth"]) < 800) || (std::stoi(ini["Display"]["resolutionWidth"]) > width))
        {
            ini["Display"]["resolutionWidth"] = std::to_string(width);
            file.write(ini);
        }

        if ((ini["Display"]["resolutionHeight"].empty()) || (std::stoi(ini["Display"]["resolutionHeight"]) < 600) || (std::stoi(ini["Display"]["resolutionHeight"]) > height))
        {
            ini["Display"]["resolutionHeight"] = std::to_string(height);
            file.write(ini);
        }

        if (ini["Display"]["refreshRate"].empty() || ini["Display"]["refreshRate"] != "60" || ini["Display"]["refreshRate"] != "120" || ini["Display"]["refreshRate"] != "144")
        {
            ini["Display"]["refreshRate"] = std::to_string(refreshRate);
            file.write(ini);
        }

        if ((ini["Display"]["fullscreen"].empty()) ||
            (ini["Display"]["fullscreen"] != "0" && ini["Display"]["fullscreen"] != "1"))
        {

            ini["Display"]["fullscreen"] = getFullscreen() ? "1" : "0";
            file.write(ini);
        }

        if ((ini["Display"]["vSync"].empty()) ||
            (ini["Display"]["vSync"] != "0" && ini["Display"]["vSync"] != "1"))
        {

            ini["Display"]["vSync"] = getVSync() ? "1" : "0";
            file.write(ini);
        }
    }

public:
    // Constructor
    SettingsManager();

    // Destructor
    ~SettingsManager();

    // SET Width
    void setWidth(int w) { width = w; }
    // SET Height
    void setHeight(int h) { height = h; }
    // SET Refresh Rate
    void setRefreshRate(int hz) { refreshRate = hz; }
    // SET Fullscreen
    void setFullscreen(bool fs) { fullscreen = fs; }
    // SET VSync
    void setVSync(bool vs) { vSync = vs; }
    // SET Monitor
    void setMonitor(GLFWmonitor *m) { monitor = m; }

    // GET Width
    int getWidth() { return width; }
    // GET Height
    int getHeight() { return height; }
    // GET Refresh Rate
    int getRefreshRate() { return refreshRate; }
    // GET Fullscreen
    bool getFullscreen() { return fullscreen; }
    // GET VSync
    bool getVSync() { return vSync; }
    // GET Monitor
    GLFWmonitor *getMonitor() { return monitor; }
    // GET Title
    const char *getTitle() { return title; }

    // GET All Monitors with Resolutions
    std::vector<Monitor> getAllMonitorsWithResolutions();

    // GET Default Monitor Resolution
    ScreenResolution getDefaultDisplayResolution();
};

#endif // SETTINGSMANAGER_H