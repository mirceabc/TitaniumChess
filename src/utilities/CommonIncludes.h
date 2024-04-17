#ifndef COMMON_INCLUDES_H
#define COMMON_INCLUDES_H

#ifdef __APPLE__               // For MacOS
#define GL_SILENCE_DEPRECATION // To silence deprecation warnings on MacOS
#endif                         // __APPLE__

#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#endif // COMMON_INCLUDES_H