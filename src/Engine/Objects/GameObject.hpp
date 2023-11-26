#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../../Common.h"

class GameObject
{
protected:
    glm::vec3 position;

    std::vector<GameObject*> children;

public:
    /* Sets the position vector to new vector
    *  @param newPosition new vec3 to set position to. */
    void Move(glm::vec3 newPosition);

    void AddChild(GameObject* object) {children.push_back(object);}

    inline glm::vec3 getPosition() {return position;}
};

#endif // GAME_OBJECT_H
