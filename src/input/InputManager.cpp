#include "InputManager.h"

// Constructor
InputManager::InputManager(GLFWwindow* window){
    this->window = window;
}

// Destructor
InputManager::~InputManager(){}

// Process the input
void InputManager::processInput(){

    // Close the window when the user presses the ESC key
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    //Add new input handling here
}