#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../utilities/CommonIncludes.h"

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

#endif // INPUT_MANAGER_H