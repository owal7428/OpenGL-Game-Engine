#include "Texture.hpp"

#include "Utility/util.h"
#include "../Vendor/stb_image/stb_image.h"

//#define USE_STB

Texture::Texture(const char* path)
{
    filePath = path;
    
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    #ifdef USE_STB

    // Flip is necessary due to images being displayed bottom-left to top-right
    stbi_set_flip_vertically_on_load(1);
    data = stbi_load(filePath, &width, &height, &bitDepth, 3);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    // Check failure to load
    if (!data)
        fprintf(stderr, "ERROR: Failed to load texture from %s\n", filePath);
    else
        stbi_image_free(data);
    
    #else

    ID = LoadTexBMP(path);
    
    glBindTexture(GL_TEXTURE_2D, 0);

    #endif
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
