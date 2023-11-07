#ifndef STAR_H
#define STAR_H

#include "Brush.hpp"

#include "../../Texture.hpp"

class Star : public Brush
{
private:
    Texture* texture;

    void drawUntextured(int emission, float shiny);
    void drawTextured(int emission, float shiny);

public:
    // Textured constructor
    Star(const char* textureFile, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    
    // Non-textured constructor
    Star(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    ~Star();

    void Draw(int emission, float shiny);
};

#endif // STAR_H