#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Rhombus : public Brush
{
private:
    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Rhombus(const char* textureFile,
            float x, float y, float z,
            float rot_x, float rot_y, float rot_z,
            float scale_x, float scale_y, float scale_z);
    
    // Non-textured constructor
    Rhombus(float x, float y, float z,
            float rot_x, float rot_y, float rot_z,
            float scale_x, float scale_y, float scale_z);
};

#endif // RHOMBUS_H