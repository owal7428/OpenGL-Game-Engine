#include "Plane.hpp"

#include "../../Utility/util.h"

Plane::Plane(Shader* shaderFile, const char* textureFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z) : Brush(shaderFile, textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front            // Normals      // Texture coordinates
        -0.5, -0.5, 0,      0, 0, 1,        0, 0,
        0.5, -0.5, 0,       0, 0, 1,        1, 0,
        0.5, 0.5, 0,        0, 0, 1,        1, 1,
        -0.5, 0.5, 0,       0, 0, 1,        0, 1,
    };

    this -> VAO = new VertexArray(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 4;
}

Plane::Plane(Shader* shaderFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z) : Brush(shaderFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    std::vector<float> temp =
    {
        // Front            // Normals      // Texture coordinates
        -0.5, -0.5, 0,      0, 0, 1,        0, 0,
        0.5, -0.5, 0,       0, 0, 1,        1, 0,
        0.5, 0.5, 0,        0, 0, 1,        1, 1,
        -0.5, 0.5, 0,       0, 0, 1,        0, 1,
    };

    this -> VAO = new VertexArray(&temp);
    this -> primitiveType = GL_QUADS;
    this -> numVertices = 4;
}
