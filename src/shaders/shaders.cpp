#include "Shaders.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
   GLuint vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
   GLuint fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

   programID = glCreateProgram();
   glAttachShader(programID, vertexShader);
   glAttachShader(programID, fragmentShader);
   glLinkProgram(programID);

   GLint success;
   GLchar infoLog[1024];
   glGetProgramiv(programID, GL_LINK_STATUS, &success);
   if(!success){
       glGetProgramInfoLog(programID, 1024, NULL, infoLog);
       std::cerr << "Error: Shader program linking failed\n" << infoLog << std::endl;
   }
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
}

void Shader::use(){
    glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setVec3(const std::string &name, glm::vec3 &value) const{
    glUniform3fv(glGetUniformLocation(programID, name.c_str()), 1, glm::value_ptr(value));
}

void Shader::setMat4(const std::string &name, glm::mat4 &value) const{
    glUniformMatrix4fv(glGetUniformLocation(programID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::getProgramID(){
    return programID;
}

Shader::~Shader(){
    glDeleteProgram(programID);
}

GLuint Shader::loadShader(const char* path, GLenum shaderType){
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try{
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();
        shaderCode = shaderStream.str();
    } catch(std::ifstream::failure e){
        std::cerr << "Error: Shader file not successfully read" << std::endl;
    }

    const char* shaderCodeCStr = shaderCode.c_str();
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &shaderCodeCStr, NULL);
    glCompileShader(shaderID);
    checkCompileErrors(shaderID, "SHADER");

    return shaderID;
}

void Shader::checkCompileErrors(GLuint shader, std::string shaderType){

    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        std::cerr << "Error: " << shaderType << " compilation failed\n" << infoLog << std::endl;
    }
}