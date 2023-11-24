#include "Brush.hpp"

#include "../../Utility/util.h"

Brush::Brush(const char* textureFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z)
{
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

    this -> hasShader = false;
}

Brush::Brush(float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z)
{
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

    this -> hasShader = false;
}

Brush::~Brush()
{
    if (texture != nullptr)
        delete texture;
    
    if (VAO != nullptr)
        delete VAO;
}

void Brush::Draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 lightColor, float ambient)
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

    glm::mat4 view = glm::translate(viewMatrix, position);

    glm::mat4 model = glm::toMat4(externalRotations * rotation);
    model = glm::scale(model, scale);

    glm::mat4 MVP = projectionMatrix * view * model;

    int matrixLocation = glGetUniformLocation(shader -> getID(), "MVP");
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(MVP));

    int colorLocation = glGetUniformLocation(shader -> getID(), "vertexColor");
    glUniform4f(colorLocation, color.x, color.y, color.z, 1.0f);

    int lightColorLocation = glGetUniformLocation(shader -> getID(), "lightColor");
    glUniform3f(lightColorLocation, lightColor.x, lightColor.y, lightColor.z);

    int ambientLocation = glGetUniformLocation(shader -> getID(), "ambientStrength");
    glUniform1f(ambientLocation, ambient);

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
