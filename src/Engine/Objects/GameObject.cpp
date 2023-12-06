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

void GameObject::MoveVelocity(glm::vec3 newVelocity)
{
    glm::vec3 deltaVelocity = newVelocity - velocity;

    velocity = newVelocity;

    int size = children.size();
    for (int i = 0; i < size; i++)
    {
        glm::vec3 oldVelocity = children.at(i) -> getVelocity();
        glm::vec3 newVel = oldVelocity + deltaVelocity;

        children.at(i) -> MoveVelocity(newVel);
    }
}

void GameObject::Update(double deltaTime)
{
    Move(position + glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, velocity.z * deltaTime));
}
