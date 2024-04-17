#ifndef EBO_H
#define EBO_H

#include "../utilities/CommonIncludes.h"

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