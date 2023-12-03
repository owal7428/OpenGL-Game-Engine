#ifndef PLANE_COLLIDER_H
#define PLANE_COLLIDER_H

#include "Collider.hpp"

class PlaneCollider : public Collider
{
private:

public:
    PlaneCollider(Brush* actor, glm::vec3 position, glm::quat rotation, glm::vec3 scale, double* xPos, double* yPos, double* zPos);

    void CollisionTest(glm::vec3 playerPosition);
};

#endif // PLANE_COLLIDER_H
