#include "Texture.hpp"

#include "../Vendor/stb/stb_image.h"

Texture::Texture(unsigned int id, const std::string path)
{
    ID = id;
    filePath = path;
    //glGenTextures();
}

Texture::~Texture()
{

}
    
void Texture::Bind()
{
    
}

void Texture::Unbind()
{

}
