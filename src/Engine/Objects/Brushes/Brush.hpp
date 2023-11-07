#ifndef BRUSH_H
#define BRUSH_H

#include "../../../Common.h"

class Brush
{
protected:
    bool hasTexture;

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    
public:
    Brush() {}

    inline void Move(glm::vec3 newPosition) {position = newPosition;}

    inline glm::vec3 getLocation() {return position;}
};

#endif // BRUSH_H
