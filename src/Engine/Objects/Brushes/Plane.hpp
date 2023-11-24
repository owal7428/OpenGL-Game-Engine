#ifndef PLANE_H
#define PLANE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Plane : public Brush
{
public:
    // Textured constructor
    Plane(Shader* shaderFile, const char* textureFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
    
    // Non-textured constructor
    Plane(Shader* shaderFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
};

#endif // PLANE_H
