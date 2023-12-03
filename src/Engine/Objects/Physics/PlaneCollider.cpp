#include "PlaneCollider.hpp"

PlaneCollider::PlaneCollider(Brush* actor, glm::vec3 position, glm::quat rotation, glm::vec3 scale, double* xPos, double* yPos, double* zPos) : Collider(actor, xPos, yPos, zPos)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = model * glm::toMat4(rotation);
    model = glm::scale(model, scale);

    glm::vec4 vertex1 = model * glm::vec4(-0.5, -0.5, 0, 1);
    glm::vec4 vertex2 = model * glm::vec4(0.5, -0.5, 0, 1);
    glm::vec4 vertex3 = model * glm::vec4(0.5, 0.5, 0, 1);
    glm::vec4 vertex4 = model * glm::vec4(-0.5, 0.5, 0, 1);

    vertices.push_back(glm::vec3(vertex1));
    vertices.push_back(glm::vec3(vertex2));
    vertices.push_back(glm::vec3(vertex3));
    vertices.push_back(glm::vec3(vertex4));

    glm::vec3 normal = glm::transpose(glm::inverse(glm::mat3(model))) * glm::vec3(0,0,1);

    normal = glm::normalize(normal);

    normals.push_back(normal);
}

void PlaneCollider::CollisionTest(glm::vec3 playerPosition)
{
    glm::vec3 shortestAxis;
    float overlapMagnitude = INT_MAX;

    std::vector<glm::vec3> axes(normals);

    // Axes for plane edges
    axes.push_back(glm::normalize(vertices[1] - vertices[0]));
    axes.push_back(glm::normalize(vertices[3] - vertices[0]));

    // Normal vectors for player collider
    axes.push_back(glm::vec3(1, 0, 0));
    axes.push_back(glm::vec3(0, 1, 0));
    axes.push_back(glm::vec3(0, 0, 1));

    std::vector<glm::vec3> playerVertices;

    // Vertices of player collider
    playerVertices.push_back(glm::vec3(-0.5, -2, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, -2, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, 0.25, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(-0.5, 0.25, -0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(-0.5, -2, 0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, -2, 0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(0.5, 0.25, 0.5) + playerPosition);
    playerVertices.push_back(glm::vec3(-0.5, 0.25, 0.5) + playerPosition);

    int size = axes.size();
    for (int i = 0; i < size; i++)
    {
        glm::vec2 objectProjection = getProjectionForAxis(axes[i], vertices);
        glm::vec2 playerProjection = getProjectionForAxis(axes[i], playerVertices); 

        // Get the length of overlap
        float intersectionLength = doProjectionsCollide(objectProjection, playerProjection);

        if (intersectionLength == 0)
        {
            actor -> setColor(0.5,0.5,0.5);
            return;
        }

        float intersectMagnitude = intersectionLength < 0 ? (intersectionLength * -1) : intersectionLength;

        if (intersectMagnitude < overlapMagnitude)
        {
            shortestAxis = axes[i] * (intersectionLength * 1.01f);
            overlapMagnitude = intersectMagnitude;
        }
    }

    Response(-shortestAxis);
    actor -> setColor(1,0,0);
}
