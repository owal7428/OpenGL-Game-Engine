#ifndef COLLIDER_H
#define COLLIDER_H

#include "../../../Common.h"

#include "../GameObject.hpp"
#include "../Brushes/Brush.hpp"

class Collider : public GameObject
{
private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;

    Brush* test;

public:
    Collider(Brush* test);

    void CollisionTest(glm::vec3 playerPosition);
};

#endif // COLLIDER_H
