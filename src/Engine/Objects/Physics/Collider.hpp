#ifndef COLLIDER_H
#define COLLIDER_H

#include "../../../Common.h"

#include "../GameObject.hpp"

class Collider : public GameObject
{
protected:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    GameObject* actor;

    float doProjectionsCollide(glm::vec2 p1, glm::vec2 p2);
    glm::vec2 getProjectionForAxis(glm::vec3 axis, std::vector<glm::vec3> vertices);

public:
    Collider(GameObject* actor);

    virtual void CollisionTest(glm::vec3 playerPosition) = 0;
    
    void Response(glm::vec3 exitVector);
};

#endif // COLLIDER_H
