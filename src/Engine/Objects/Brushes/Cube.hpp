#ifndef CUBE_H
#define CUBE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Cube : public Brush
{
public:
    // Textured constructor
    Cube(Shader* shaderFile, const char* textureFile,
         float x, float y, float z,
         float rot_x, float rot_y, float rot_z,
         float scale_x, float scale_y, float scale_z);
    
    // Non-textured constructor
    Cube(Shader* shaderFile,
         float x, float y, float z,
         float rot_x, float rot_y, float rot_z,
         float scale_x, float scale_y, float scale_z);
};

#endif // CUBE_H
