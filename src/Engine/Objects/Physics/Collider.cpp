#include "Collider.hpp"

glm::vec2 Collider::getProjectionForAxis(glm::vec3 axis, std::vector<glm::vec3> vertices)
{
    double min = glm::dot(axis, vertices[0]);
    double max = min;

    int size = vertices.size();
    for (int i = 1; i < size; i++)
    {
        double point = glm::dot(axis, vertices[i]);

        if (point < min) min = point;
        if (point > max) max = point;
    }

    return glm::vec2(min, max);
}

bool Collider::doProjectionsCollide(glm::vec2 p1, glm::vec2 p2)
{
    if (p2.x > p1.x && p2.x < p1.y)
        return true;

    else if (p2.y >= p1.x && p2.y <= p1.y)
        return true;
    
    else if (p1.x >= p2.x && p1.x <= p2.y)
        return true;
    
    else if (p1.y >= p2.x && p1.y <= p2.y)
        return true;

    else 
        return false;
}
