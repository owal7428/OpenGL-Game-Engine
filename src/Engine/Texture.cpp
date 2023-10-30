#include "Texture.hpp"

#include "Utility/util.h"

//#define STBI_MSC_SECURE_CRT
//#define STB_IMAGE_IMPLEMENTATION
//#include "../Vendor/stb/stb_image.h"

Texture::Texture(const char* path)
{
    filePath = path;
    
    //glGenTextures(1, &ID);
    //glBindTexture(GL_TEXTURE_2D, ID);

    //data = stbi_load(filePath, &width, &height, &bitDepth, 4);
    ID = LoadTexBMP(path);

    /*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB8, GL_UNSIGNED_BYTE, data);*/
    //glGenerateMipmap(GL_TEXTURE_2D);

    //glBindTexture(GL_TEXTURE_2D, 0);

    // Check failure to load
    if (!data)
        fprintf(stderr, "ERROR: Failed to load texture from %s\n", filePath);
    //else
        //stbi_image_free(data);
}

Texture::~Texture()
{
    glDeleteTextures(1, &ID);
}
    
void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
