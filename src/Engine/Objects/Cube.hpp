#ifndef CUBE_H
#define CUBE_H

#include "../Texture.hpp"

class Cube
{
private:
    bool hasTexture;
    float x, y, z, scale_x, scale_y, scale_z, th, ph, ze;

    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Cube(const char* textureFile, float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);
    
    // Non-textured constructor
    Cube(float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);

    ~Cube();

    void Draw(int emission, float shiny);
};

#endif // CUBE_H