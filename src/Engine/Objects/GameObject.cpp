#include "GameObject.hpp"

void GameObject::Move(glm::vec3 newPosition)
{
    glm::vec3 deltaPosition = newPosition - position;

    position = newPosition;

    int size = children.size();
    for (int i = 0; i < size; i++)
    {
        glm::vec3 oldPosition = children.at(i) -> getPosition();
        glm::vec3 newPos = oldPosition + deltaPosition;

        children.at(i) -> Move(newPos);
    }
}
