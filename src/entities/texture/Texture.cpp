#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "Texture.h"

Texture::Texture(const std::string& path){

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int textureWidth, textureHeight, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &textureWidth, &textureHeight, &nrChannels, 0);
    if(data){
        if(nrChannels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else if(nrChannels == 4){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureWidth, textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else{
        std::cerr << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture(){
    glBindTexture(GL_TEXTURE_2D, 0);
    glDeleteTextures(1, &m_ID);
}

void Texture::Bind(){
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}   