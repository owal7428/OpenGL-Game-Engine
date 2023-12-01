#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

#include "Collider.hpp"

class PlaneCollider : public Collider
{
private:

public:
    PlaneCollider(Brush* test, glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    void CollisionTest(glm::vec3 playerPosition);
};

#endif // PLANE_COLLIDER_H
