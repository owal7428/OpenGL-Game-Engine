#ifndef BRUSH_H
#define BRUSH_H

#include "../../../Common.h"
#include "../../Texture.hpp"

class Brush
{
protected:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    bool hasTexture;

    Texture* texture;
    

public:
    Brush() {}

    // Textured constructor
    Brush(const char* textureFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);

    // Non-textured constructor
    Brush(float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
    
    ~Brush();

    void Draw(int emission, float shiny);

    void Move(glm::vec3 newPosition) {position = newPosition;}

    inline glm::vec3 getPosition() {return position;}

private:
    virtual void drawUntextured(int emission, float shiny) = 0;
    virtual void drawTextured(int emission, float shiny) = 0;
};

#endif // BRUSH_H
