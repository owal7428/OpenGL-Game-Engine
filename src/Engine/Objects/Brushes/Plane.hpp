#ifndef PLANE_H
#define PLANE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Plane : public Brush
{
private:
    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Plane(const char* textureFile, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    // Non-textured constructor
    Plane(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    ~Plane();

    void Draw(int emission, float shiny);
};

#endif // PLANE_H