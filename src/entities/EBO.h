#ifndef EBO_H
#define EBO_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

class EBO{
    public:
        EBO(unsigned int *indices, GLsizeiptr size);
        ~EBO();

        void Bind();
        void Unbind();
    private:
        GLuint m_ID;
};

#endif // EBO_H