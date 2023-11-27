#include "Rhombus.hpp"

#include "../../Utility/util.h"

Rhombus::Rhombus(Shader* shaderFile, const char* textureFile,
                 float x, float y, float z,
                 float rot_x, float rot_y, float rot_z,
                 float scale_x, float scale_y, float scale_z) : Brush(shaderFile, textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front face   // Normals      // Texture coordinates
        -0.5, -0.5, -0.5,     0, -1, 1,       0, 0,
        0.5, -0.5, -0.5,      0, -1, 1,       1, 0,
        0.5, 0.5, 0.5,        0, -1, 1,       1, 1,
        -0.5, 0.5, 0.5,       0, -1, 1,       0, 1,

        //  Back face
        0.5, -0.5, -1.5,      0, 1, -1,       0, 0,
        -0.5, -0.5, -1.5,     0, 1, -1,       1, 0,
        -0.5, 0.5, -0.5,      0, 1, -1,       1, 1,
        0.5, 0.5, -0.5,       0, 1, -1,       0, 1,
        
        //  Right face
        0.5, -0.5, -0.5,      1, 0, 0,        0, 0,
        0.5, -0.5, -1.5,      1, 0, 0,        1, 0,
        0.5, 0.5, -0.5,       1, 0, 0,        1, 1,
        0.5, 0.5, 0.5,        1, 0, 0,        0, 1,
        
        //  Left face
        -0.5, -0.5, -1.5,     -1, 0, 0,       0, 0,
        -0.5, -0.5, -0.5,     -1, 0, 0,       1, 0,
        -0.5, 0.5, 0.5,       -1, 0, 0,       1, 1,
        -0.5, 0.5, -0.5,      -1, 0, 0,       0, 1,
        
        //  Top face
        -0.5, 0.5, 0.5,       0, 1, 0,        0, 0,
        0.5, 0.5, 0.5,        0, 1, 0,        1, 0,
        0.5, 0.5, -0.5,       0, 1, 0,        1, 1,
        -0.5, 0.5, -0.5,      0, 1, 0,        0, 1,
        
        //  Bottom face
        -0.5, -0.5, -1.5,     0, -1, 0,       0, 0,
        0.5, -0.5, -1.5,      0, -1, 0,       1, 0,
        0.5, -0.5, -0.5,      0, -1, 0,       1, 1,
        -0.5, -0.5, -0.5,     0, -1, 0,       0, 1,
    };

    this -> VAO = new VertexArray(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 24;
}

Rhombus::Rhombus(Shader* shaderFile,
                 float x, float y, float z,
                 float rot_x, float rot_y, float rot_z,
                 float scale_x, float scale_y, float scale_z) : Brush(shaderFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front face   // Normals      // Texture coordinates
        -1, -1, -1,     0, -1, 1,       0, 0,
        1, -1, -1,      0, -1, 1,       1, 0,
        1, 1, 1,        0, -1, 1,       1, 1,
        -1, 1, 1,       0, -1, 1,       0, 1,

        //  Back face
        1, -1, -3,      0, 1, -1,       0, 0,
        -1, -1, -3,     0, 1, -1,       1, 0,
        -1, 1, -1,      0, 1, -1,       1, 1,
        1, 1, -1,       0, 1, -1,       0, 1,
        
        //  Right face
        1, -1, -1,      1, 0, 0,        0, 0,
        1, -1, -3,      1, 0, 0,        1, 0,
        1, 1, -1,       1, 0, 0,        1, 1,
        1, 1, 1,        1, 0, 0,        0, 1,
        
        //  Left face
        -1, -1, -3,     -1, 0, 0,       0, 0,
        -1, -1, -1,     -1, 0, 0,       1, 0,
        -1, 1, 1,       -1, 0, 0,       1, 1,
        -1, 1, -1,      -1, 0, 0,       0, 1,
        
        //  Top face
        -1, 1, 1,       0, 1, 0,        0, 0,
        1, 1, 1,        0, 1, 0,        1, 0,
        1, 1, -1,       0, 1, 0,        1, 1,
        -1, 1, -1,      0, 1, 0,        0, 1,
        
        //  Bottom face
        -1, -1, -3,     0, -1, 0,       0, 0,
        1, -1, -3,      0, -1, 0,       1, 0,
        1, -1, -1,      0, -1, 0,       1, 1,
        -1, -1, -1,     0, -1, 0,       0, 1,
    };

    this -> VAO = new VertexArray(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 24;
}
