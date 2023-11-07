#ifndef PLANE_H
#define PLANE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Plane : public Brush
{
private:
    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Plane(const char* textureFile, float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);
    
    // Non-textured constructor
    Plane(float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);

    ~Plane();

    void Draw(int emission, float shiny);
};

#endif // PLANE_H