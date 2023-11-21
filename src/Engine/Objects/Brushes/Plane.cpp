#include "Plane.hpp"

#include "../../Utility/util.h"

Plane::Plane(const char* textureFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z) : Brush(textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front        // Normals      // Texture coordinates
        -1, -1, 0,      0, 0, 1,        0, 0,
        1, -1, 0,       0, 0, 1,        1, 0,
        1, 1, 0,        0, 0, 1,        1, 1,
        -1, 1, 0,       0, 0, 1,        0, 1,
    };

    this -> buffer = new VertexBuffer(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 4;
}

Plane::Plane(float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z) : Brush(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front        // Normals      // Texture coordinates
        -1, -1, 0,      0, 0, 1,        0, 0,
        1, -1, 0,       0, 0, 1,        1, 0,
        1, 1, 0,        0, 0, 1,        1, 1,
        -1, 1, 0,       0, 0, 1,        0, 1,
    };

    this -> buffer = new VertexBuffer(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 4;
}
