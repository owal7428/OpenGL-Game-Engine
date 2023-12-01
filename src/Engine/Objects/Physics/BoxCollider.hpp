#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "Collider.hpp"

class BoxCollider : public Collider
{
private:

public:
    BoxCollider(Brush* test, glm::vec3 position, glm::quat rotation, glm::vec3 scale);

    void CollisionTest(glm::vec3 playerPosition);
};

#endif // BOX_COLLIDER_H
