#ifndef CUBE_H
#define CUBE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Cube : public Brush
{
private:
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
};

#endif // CUBE_H