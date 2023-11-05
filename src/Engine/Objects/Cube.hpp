#ifndef CUBE_H
#define CUBE_H

#include "../Texture.hpp"

class Cube
{
private:
    bool hasTexture;
    float x, y, z, scale_x, scale_y, scale_z, th, ph, ze;

    Texture* textures[6];

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Cube(const char* textureFiles[6], float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);
    
    // Non-textured constructor
    Cube(float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);

    ~Cube();

    void Draw(int emission, float shiny);
    inline void Move(float x_new, float y_new, float z_new) {x = x_new; y = y_new; z = z_new;}
};

#endif // CUBE_H