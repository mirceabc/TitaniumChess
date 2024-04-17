#ifndef VAO_H
#define VAO_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "VBO.h"

class VAO{
    public:
    VAO();
    ~VAO();

    void Bind();
    void Unbind();
    void AddBuffer(VBO& vbo, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset);

    private:
        GLuint m_ID;
};

#endif