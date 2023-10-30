#ifndef TEXTURE_H
#define TEXTURE_H

#include "../Common.h"

class Texture
{
private:
    unsigned int ID;
    std::string filePath;
    unsigned char* buffer;
    int width, height, BPP;
public:
    Texture(unsigned int ID, const std::string path);
    ~Texture();
    
    void Bind();
    void Unbind();
};

#endif // TEXTURE_H
