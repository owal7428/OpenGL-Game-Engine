#include "Brush.hpp"

#include "../../Utility/util.h"

Brush::Brush(Shader* shaderFile, const char* textureFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z)
{
    shader = shaderFile;

    texture = new Texture(textureFile);

    hasTexture = true;

    this -> position    = glm::vec3(x, y, z);
    this -> scale       = glm::vec3(scale_x, scale_y, scale_z);

    // Build quaternions for x, y, and z axis rotations, then combine
    glm::quat quat_x = glm::angleAxis(glm::radians(rot_x), glm::vec3(1,0,0));
    glm::quat quat_y = glm::angleAxis(glm::radians(rot_y), glm::vec3(0,1,0));
    glm::quat quat_z = glm::angleAxis(glm::radians(rot_z), glm::vec3(0,0,1));

    this -> rotation = quat_x * quat_y * quat_z;
    this -> externalRotations = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

    this -> drawWireFrame = false;

    this -> color = glm::vec3(1.0f, 1.0f, 1.0f);
}

Brush::Brush(Shader* shaderFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z)
{
    shader = shaderFile;
    
    texture = nullptr;
    
    hasTexture = false;

    this -> position    = glm::vec3(x, y, z);
    this -> scale       = glm::vec3(scale_x, scale_y, scale_z);

    // Build quaternions for x, y, and z axis rotations, then combine
    glm::quat quat_x = glm::angleAxis(glm::radians(rot_x), glm::vec3(1,0,0));
    glm::quat quat_y = glm::angleAxis(glm::radians(rot_y), glm::vec3(0,1,0));
    glm::quat quat_z = glm::angleAxis(glm::radians(rot_z), glm::vec3(0,0,1));

    this -> rotation = quat_x * quat_y * quat_z;
    this -> externalRotations = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));

    this -> drawWireFrame = false;

    this -> color = glm::vec3(1.0f, 1.0f, 1.0f);
}

Brush::~Brush()
{
    if (texture != nullptr)
        delete texture;
    
    if (VAO != nullptr)
        delete VAO;
}

void Brush::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 lightPosition, glm::vec3 lightColor, float ambient)
{
    VAO -> Bind();
    shader -> Activate();

    if (hasTexture)
    {
        texture -> Bind();
    }
    
    if (drawWireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = model * glm::toMat4(externalRotations * rotation);
    model = glm::scale(model, scale);

    shader -> setUniformMat4("model", &model);
    shader -> setUniformMat4("view", &viewMatrix);
    shader -> setUniformMat4("projection", &projectionMatrix);

    shader -> setUniform4f("vertexColor", color.x, color.y, color.z, 1.0f);

    shader -> setUniform3f("lightPos", lightPosition.x, lightPosition.y, lightPosition.z);
    shader -> setUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);

    shader -> setUniform1f("ambientIntensity", ambient);

    glDrawArrays(primitiveType, 0, numVertices);

    if (drawWireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    if (hasTexture)
    {
        texture -> Unbind();
    }

    shader -> Deactivate();
    VAO -> Unbind();
}
