#include "Cube.hpp"

#include "../../Utility/util.h"

Cube::Cube(Shader* shaderFile, const char* textureFile,
           float x, float y, float z,
           float rot_x, float rot_y, float rot_z,
           float scale_x, float scale_y, float scale_z) : Brush(shaderFile, textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front        // Normals      // Texture coordinates
        -1, -1, 1,      0, 0, 1,        0, 0,
        1, -1, 1,       0, 0, 1,        1, 0,
        1, 1, 1,        0, 0, 1,        1, 1,
        -1, 1, 1,       0, 0, 1,        0, 1,

        //  Back
        1, -1, -1,      0, 0, -1,       0, 0,
        -1, -1, -1,     0, 0, -1,       1, 0,
        -1, 1, -1,      0, 0, -1,       1, 1,
        1, 1, -1,       0, 0, -1,       0, 1,
        
        //  Left
        -1, -1, -1,     -1, 0, 0,       0, 0,
        -1, -1, 1,      -1, 0, 0,       1, 0,
        -1, 1, 1,       -1, 0, 0,       1, 1,
        -1, 1, -1,      -1, 0, 0,       0, 1,

        //  Right
        1, -1, 1,       1, 0, 0,        0, 0,
        1, -1, -1,      1, 0, 0,        1, 0,
        1, 1, -1,       1, 0, 0,        1, 1,
        1, 1, 1,        1, 0, 0,        0, 1,
        
        //  Top
        -1, 1, 1,       0, 1, 0,        0, 0,
        1, 1, 1,        0, 1, 0,        1, 0,
        1, 1, -1,       0, 1, 0,        1, 1,
        -1, 1, -1,      0, 1, 0,        0, 1,

        //  Bottom
        -1, -1, -1,     0, -1, 0,       0, 0,
        1, -1, -1,      0, -1, 0,       1, 0,
        1, -1, 1,       0, -1, 0,       1, 1,
        -1, -1, 1,      0, -1, 0,       0, 1,
    };

    this -> VAO = new VertexArray(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 24;
}


Cube::Cube(Shader* shaderFile,
           float x, float y, float z,
           float rot_x, float rot_y, float rot_z,
           float scale_x, float scale_y, float scale_z) : Brush(shaderFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front        // Normals      // Texture coordinates
        -1, -1, 1,      0, 0, 1,        0, 0,
        1, -1, 1,       0, 0, 1,        1, 0,
        1, 1, 1,        0, 0, 1,        1, 1,
        -1, 1, 1,       0, 0, 1,        0, 1,

        //  Back
        1, -1, -1,      0, 0, -1,       0, 0,
        -1, -1, -1,     0, 0, -1,       1, 0,
        -1, 1, -1,      0, 0, -1,       1, 1,
        1, 1, -1,       0, 0, -1,       0, 1,
        
        //  Left
        -1, -1, -1,     -1, 0, 0,       0, 0,
        -1, -1, 1,      -1, 0, 0,       1, 0,
        -1, 1, 1,       -1, 0, 0,       1, 1,
        -1, 1, -1,      -1, 0, 0,       0, 1,

        //  Right
        1, -1, 1,       1, 0, 0,        0, 0,
        1, -1, -1,      1, 0, 0,        1, 0,
        1, 1, -1,       1, 0, 0,        1, 1,
        1, 1, 1,        1, 0, 0,        0, 1,
        
        //  Top
        -1, 1, 1,       0, 1, 0,        0, 0,
        1, 1, 1,        0, 1, 0,        1, 0,
        1, 1, -1,       0, 1, 0,        1, 1,
        -1, 1, -1,      0, 1, 0,        0, 1,

        //  Bottom
        -1, -1, -1,     0, -1, 0,       0, 0,
        1, -1, -1,      0, -1, 0,       1, 0,
        1, -1, 1,       0, -1, 0,       1, 1,
        -1, -1, 1,      0, -1, 0,       0, 1,
    };

    this -> VAO = new VertexArray(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 24;
}
