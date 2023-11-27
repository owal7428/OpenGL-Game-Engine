#include "Collider.hpp"

Collider::Collider(Brush* test)
{
    this -> test = test;

    glm::vec3 vertex1 = glm::vec3(-1, -1, 0);
    glm::vec3 vertex2 = glm::vec3(1, -1, 0);
    glm::vec3 vertex3 = glm::vec3(1, 1, 0);
    glm::vec3 vertex4 = glm::vec3(-1, 1, 0);

    vertices.push_back(vertex1);
    vertices.push_back(vertex2);
    vertices.push_back(vertex3);
    vertices.push_back(vertex4);

    normals.push_back(glm::vec3(0,0,1));
}

glm::vec2 getProjectionForAxis(glm::vec3 axis, std::vector<glm::vec3> vertices)
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

bool doProjectionsCollide(glm::vec2 p1, glm::vec2 p2)
{
    if (p2.x > p1.x && p2.x < p1.y)
        return true;

    else if (p2.y > p1.x && p2.y < p1.y)
        return true;
    
    else if (p1.x > p2.x && p1.x < p2.y)
        return true;
    
    else if (p1.y > p2.x && p1.y < p2.y)
        return true;

    else 
        return false;
}

void Collider::CollisionTest(glm::vec3 playerPosition)
{
    std::vector<glm::vec3> axes(normals);

    axes.push_back(glm::vec3(1, 0, 0));
    axes.push_back(glm::vec3(0,1,0));

    std::vector<glm::vec3> playerVertices;

    playerVertices.push_back(glm::vec3(-0.5, -2, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, -2, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, 0, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(-0.5, 0, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(-0.5, -2, 0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, -2, 0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, 0, 0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(-0.5, 0, 0.5) + playerPosition);

    int size = axes.size();
    for (int i = 0; i < size; i++)
    {
        glm::vec2 objectProjection = getProjectionForAxis(axes[i], vertices);
        glm::vec2 playerProjection = getProjectionForAxis(axes[i], playerVertices); 

        if (!doProjectionsCollide(objectProjection, playerProjection))
        {
            test -> setColor(0.5,0.5,0.5);
            return;
        }
    }

    test -> setColor(1,0,0);
}
