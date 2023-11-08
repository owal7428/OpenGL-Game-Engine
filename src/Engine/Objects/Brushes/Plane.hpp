#ifndef PLANE_H
#define PLANE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Plane : public Brush
{
private:
    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Plane(const char* textureFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
    
    // Non-textured constructor
    Plane(float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
};

#endif // PLANE_H