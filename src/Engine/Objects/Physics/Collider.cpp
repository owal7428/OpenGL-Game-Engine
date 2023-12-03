#include "Collider.hpp"

Collider::Collider(Brush* actor, double* xPos, double* yPos, double* zPos) : xPos(xPos), yPos(yPos), zPos(zPos)
{
    this -> actor = actor;
}

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

/* Returns the length of the intersection of two lines. */
float Collider::doProjectionsCollide(glm::vec2 p1, glm::vec2 p2)
{
    // Right point of object 1 is overlapping left point of object 2
    if (p1.x <= p2.x && p1.y >= p2.x)
        return -(p1.y - p2.x);
    
    // Left point of object 1 is overlapping right point of object 2
    else if (p1.y >= p2.y && p1.x <= p2.y)
        return (p2.y - p1.x);
    
    // Object 1 is contained in object 2
    else if (p1.x >= p2.x && p1.y <= p2.y)
        return (p1.y - p2.x) <= (p2.y - p1.x) ? -(p1.y - p2.x) : (p2.y - p1.x);
    
    // Object 2 is contained in object 1
    else if (p1.x <= p2.x && p1.y >= p2.y)
        return (p2.y - p1.x) <= (p1.y - p2.x) ? -(p2.y - p1.x) : (p1.y - p2.x);
    
    else return 0;

}

void Collider::Response(glm::vec3 exitVector)
{
    (*xPos) += exitVector.x;
    (*yPos) += exitVector.y;
    (*zPos) += (-exitVector.z);
}
