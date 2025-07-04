#include "VBO.h"

VBO::VBO(GLfloat* vertices, GLsizeiptr size){
    glGenBuffers(1, &m_ID);
    Bind();
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::~VBO(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_ID);
}

void VBO::Bind(){
    glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VBO::Unbind(){
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}