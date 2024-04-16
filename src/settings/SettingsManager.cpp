#include "SettingsManager.h"

// Constructor
SettingsManager::SettingsManager()
{
    getDefaultMonitorsWithResolution();
    LoadSettingsFile("settings.ini");
}

// Destructor
SettingsManager::~SettingsManager(){}