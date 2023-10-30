#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Common.h"

class Texture
{
private:
    // Set by user
    const char* filePath;

    // Used by OpenGL - Should not be set
    unsigned int ID;
    unsigned char* data;
    int width, height, bitDepth;
public:
    Texture(const char* path);
    Texture() {};
    ~Texture();
    
    void Bind();
    void Unbind();
};

#endif // TEXTURE_H
