#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Rhombus : public Brush
{
public:
    // Textured constructor
    Rhombus(Shader* shaderFile, const char* textureFile,
            float x, float y, float z,
            float rot_x, float rot_y, float rot_z,
            float scale_x, float scale_y, float scale_z);
    
    // Non-textured constructor
    Rhombus(Shader* shaderFile,
            float x, float y, float z,
            float rot_x, float rot_y, float rot_z,
            float scale_x, float scale_y, float scale_z);
};

#endif // RHOMBUS_H
