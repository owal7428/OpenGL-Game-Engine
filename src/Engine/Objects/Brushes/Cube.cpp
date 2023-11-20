#include "Cube.hpp"

#include "../../Utility/util.h"

const int numVertices = 24;

Cube::Cube(const char* textureFile,
           float x, float y, float z,
           float rot_x, float rot_y, float rot_z,
           float scale_x, float scale_y, float scale_z) : Brush(textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    vertexData.assign(
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
    });

    this -> primitiveType = GL_QUADS;
    this -> numVertices = 24;
}


Cube::Cube(float x, float y, float z,
           float rot_x, float rot_y, float rot_z,
           float scale_x, float scale_y, float scale_z) : Brush(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    vertexData.assign(
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
    });

    this -> primitiveType = GL_QUADS;
    this -> numVertices = 24;
}
