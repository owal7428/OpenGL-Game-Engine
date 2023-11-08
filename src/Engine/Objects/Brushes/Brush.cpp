#include "Brush.hpp"

Brush::Brush(const char* textureFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z)
{
    texture = new Texture(textureFile);

    hasTexture = true;

    this -> position    = glm::vec3(x, y, z);
    this -> rotation    = glm::vec3(rot_x, rot_y, rot_z);
    this -> scale       = glm::vec3(scale_x, scale_y, scale_z);
}

Brush::Brush(float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z)
{
    texture = nullptr;
    
    hasTexture = false;

    this -> position    = glm::vec3(x, y, z);
    this -> rotation    = glm::vec3(rot_x, rot_y, rot_z);
    this -> scale       = glm::vec3(scale_x, scale_y, scale_z);
}

Brush::~Brush()
{
    if (texture != nullptr)
        delete texture;
}

void Brush::Draw(int emission, float shiny)
{
    if (hasTexture)
        drawTextured(emission, shiny);
    else
        drawUntextured(emission, shiny);
}
