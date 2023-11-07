#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Rhombus : public Brush
{
private:
    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Rhombus(const char* textureFile, float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);
    
    // Non-textured constructor
    Rhombus(float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze);

    ~Rhombus();

    void Draw(int emission, float shiny);
};

#endif // RHOMBUS_H