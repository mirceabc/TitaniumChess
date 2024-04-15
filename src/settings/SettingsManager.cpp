#include "SettingsManager.h"

// Constructor
SettingsManager::SettingsManager()
{
    getDefaultMonitorsWithResolution();
    SaveDefaultSettingsFile("settings.ini");
}

// Destructor
SettingsManager::~SettingsManager(){}