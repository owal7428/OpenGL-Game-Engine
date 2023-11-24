#ifndef STAR_H
#define STAR_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Star : public Brush
{
public:
    // Textured constructor
    Star(Shader* shaderFile, const char* textureFile,
         float x, float y, float z,
         float rot_x, float rot_y, float rot_z,
         float scale_x, float scale_y, float scale_z);
    
    // Non-textured constructor
    Star(Shader* shaderFile,
         float x, float y, float z,
         float rot_x, float rot_y, float rot_z,
         float scale_x, float scale_y, float scale_z);
};

#endif // STAR_H
