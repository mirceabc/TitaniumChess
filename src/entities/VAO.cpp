#include "VAO.h"

VAO::VAO(){
    glGenVertexArrays(1, &m_ID);
}

VAO::~VAO(){
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_ID);
}

void VAO::Bind(){
    glBindVertexArray(m_ID);
}

void VAO::Unbind(){
    glBindVertexArray(0);
}

void VAO::AddBuffer(VBO& vbo, GLuint index, GLuint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset){
    Bind();
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}