#ifndef STAR_H
#define STAR_H

#include "../Texture.hpp"

class Star
{
private:
    bool hasTexture;
    float x, y, z, scale_x, scale_y, scale_z, th, ph, ze;

    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Star(const char* textureFile, float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);
    
    // Non-textured constructor
    Star(float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);

    ~Star();

    void Draw(int emission, float shiny);
};

#endif // STAR_H