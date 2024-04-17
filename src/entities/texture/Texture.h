#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../utilities/CommonIncludes.h"
#include <string>

class Texture{
    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind();
        void Unbind();
    private:
        GLuint m_ID;
};

#endif // TEXTURE_H