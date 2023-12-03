#include "BoxCollider.hpp"

BoxCollider::BoxCollider(Brush* actor, glm::vec3 position, glm::quat rotation, glm::vec3 scale, double* xPos, double* yPos, double* zPos) : Collider(actor, xPos, yPos, zPos)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = model * glm::toMat4(rotation);
    model = glm::scale(model, scale);

    glm::vec4 vertex1 = model * glm::vec4(-0.5, -0.5, 0.5, 1);
    glm::vec4 vertex2 = model * glm::vec4(0.5, -0.5, 0.5, 1);
    glm::vec4 vertex3 = model * glm::vec4(0.5, 0.5, 0.5, 1);
    glm::vec4 vertex4 = model * glm::vec4(-0.5, 0.5, 0.5, 1);
    glm::vec4 vertex5 = model * glm::vec4(-0.5, -0.5, -0.5, 1);
    glm::vec4 vertex6 = model * glm::vec4(0.5, -0.5, -0.5, 1);
    glm::vec4 vertex7 = model * glm::vec4(0.5, 0.5, -0.5, 1);
    glm::vec4 vertex8 = model * glm::vec4(-0.5, 0.5, -0.5, 1);

    vertices.push_back(glm::vec3(vertex1));
    vertices.push_back(glm::vec3(vertex2));
    vertices.push_back(glm::vec3(vertex3));
    vertices.push_back(glm::vec3(vertex4));
    vertices.push_back(glm::vec3(vertex5));
    vertices.push_back(glm::vec3(vertex6));
    vertices.push_back(glm::vec3(vertex7));
    vertices.push_back(glm::vec3(vertex8));

    glm::vec3 normal1 = glm::transpose(glm::inverse(glm::mat3(model))) * glm::vec3(1,0,0);
    glm::vec3 normal2 = glm::transpose(glm::inverse(glm::mat3(model))) * glm::vec3(0,1,0);
    glm::vec3 normal3 = glm::transpose(glm::inverse(glm::mat3(model))) * glm::vec3(0,0,1);

    normals.push_back(normal1);
    normals.push_back(normal2);
    normals.push_back(normal3);
}

void BoxCollider::CollisionTest(glm::vec3 playerPosition)
{
    glm::vec3 shortestAxis;
    float overlapMagnitude = INT_MAX;

    std::vector<glm::vec3> axes(normals);

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

    // Check edge-to-edge collision

    axes.clear();
    size = normals.size();
    for (int i = 0; i < size; i++)
    {
        axes.push_back(glm::cross(glm::vec3(1, 0, 0), normals[i]));
        axes.push_back(glm::cross(glm::vec3(0, 1, 0), normals[i]));
        axes.push_back(glm::cross(glm::vec3(0, 0, 1), normals[i]));
    }

    size = axes.size();
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
