/*
 * Copyright (c) 2024 Blaga Mircea-Constantin
 * All rights reserved.
 *
 * This file is part of Titanium Chess.
 *
 * Purpose: This is a source file for Titanium Chess, a game
 * designed for utilizing OpenGL for 3D graphics rendering.
 *
 * SPDX-License-Identifier: PRIVATE LICENSE
 * See the accompanying LICENSE file for the complete text of the license.
 */

#include "utilities/CommonIncludes.h"
#include "renderer/Core.h"
#include "renderer/WindowManager.h"
#include "input/InputManager.h"
#include "settings/SettingsManager.h"

int main(int argc, char **argv)
{
    // Create an instance of the Core class
    Core core;

    // Create an instance of the SettingsManager class
    SettingsManager settingsManager;
    
    // Create an instance of the WindowManager class
    WindowManager windowManager(settingsManager);
   
    // Get window using the settings manager
    GLFWwindow *window = windowManager.getWindow();

    // Create an instance of the InputManager class
    InputManager inputManager(window);

    // Core Main loop
    core.run(window, inputManager);

    return EXIT_SUCCESS;
}