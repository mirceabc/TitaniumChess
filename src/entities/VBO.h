#ifndef VBO_H
#define VBO_H

#include "../utilities/CommonIncludes.h"

class VBO{
    public:
        VBO(GLfloat* vertices, GLsizeiptr size);
        ~VBO();

        void Bind();
        void Unbind();

    private:
        GLuint m_ID;
};

#endif // VBO_H