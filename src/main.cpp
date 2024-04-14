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

#ifdef __APPLE__ // For MacOS
    #define GL_SILENCE_DEPRECATION
#endif // __APPLE__

#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "input/InputManager.h"

int main(int argc, char** argv) {

    // Initialize GLFW
    if(!glfwInit()){
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__ // For MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__

    GLFWwindow* window = glfwCreateWindow(800, 600, "Titanium Chess", nullptr, nullptr);
    if(!window){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0, 0, 800, 600);

    // Create an instance of the InputManager class
    InputManager inputManager(window);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        
        
        // Process the input
        inputManager.processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);


        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}