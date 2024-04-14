#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>

class InputManager{
    
    // Pointer to the GLFW window
    GLFWwindow* window;

    public:
    // Constructor
        InputManager(GLFWwindow* window = nullptr);
    // Destructor
        ~InputManager();
    // Process the input
        void processInput();
};

#endif // INPUTMANAGER_H