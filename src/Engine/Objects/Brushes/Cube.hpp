#ifndef CUBE_H
#define CUBE_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Cube : public Brush
{
private:
    Texture* textures[6];

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Cube(const char* textureFiles[6], glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    // Non-textured constructor
    Cube(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    ~Cube();

    void Draw(int emission, float shiny);
};

#endif // CUBE_H