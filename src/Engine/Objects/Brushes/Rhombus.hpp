#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Rhombus : public Brush
{
private:
    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Rhombus(const char* textureFile, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    // Non-textured constructor
    Rhombus(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    ~Rhombus();

    void Draw(int emission, float shiny);
};

#endif // RHOMBUS_H