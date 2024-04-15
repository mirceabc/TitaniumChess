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

#ifdef __APPLE__               // For MacOS
#define GL_SILENCE_DEPRECATION // To silence deprecation warnings on MacOS
#endif                         // __APPLE__

#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
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
   
    // Create a window using the settings manager
    GLFWwindow *window = windowManager.createGLFWWindow();

    // Create an instance of the InputManager class
    InputManager inputManager(window);

    // Core Main loop
    core.run(window, inputManager);

    return EXIT_SUCCESS;
}