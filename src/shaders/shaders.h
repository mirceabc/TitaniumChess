#ifndef SHADER_H
#define SHADER_H
#define GLFW_INCLUDE_NONE // We don't want GLFW to include OpenGL headers not to conflict with GLAD

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

class Shader{
    public:
        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        void use();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec3(const std::string &name, glm::vec3 &value) const;
        void setMat4(const std::string &name, glm::mat4 &value) const;
        GLuint getProgramID();
    private:
        GLuint programID;
        GLuint loadShader(const char* path, GLenum shaderType);
        void checkCompileErrors(GLuint shader, std::string shaderType);
};

#endif // SHADER_H