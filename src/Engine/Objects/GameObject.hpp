#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "../../Common.h"

class GameObject
{
protected:
    glm::vec3 position;
    glm::vec3 velocity;

    std::vector<GameObject*> children;

public:
    GameObject() {velocity = glm::vec3(0,0,0);}

    /* Sets the position vector to new vector
    *  @param newPosition new vec3 to set position to. */
    virtual void Move(glm::vec3 newPosition);

    /* Sets the velocity vector to new vector
    *  @param newVelocity new vec3 to set velocity to. */
    void MoveVelocity(glm::vec3 newVelocity);

    void Update(double deltaTime);

    void AddChild(GameObject* object) {children.push_back(object);}

    inline glm::vec3 getPosition() {return position;}
    inline glm::vec3 getVelocity() {return velocity;}
};

#endif // GAME_OBJECT_H
