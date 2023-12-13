#include "Brush.hpp"

#include "../../Utility/util.h"

#include "../Entities/Lights/PointLight.hpp"
#include "../Entities/Lights/DirectionalLight.hpp"

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

    this -> material.color = glm::vec3(0.5f, 0.5f, 0.5f);
    this -> material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    this -> material.shininess = 8;

    this -> material.textureScaleX = 1;
    this -> material.textureScaleY = 1;
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

    this -> material.color = glm::vec3(0.5f, 0.5f, 0.5f);
    this -> material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    this -> material.shininess = 8;

    this -> material.textureScaleX = 1;
    this -> material.textureScaleY = 1;
}

Brush::~Brush()
{
    if (texture != nullptr)
        delete texture;
    
    if (VAO != nullptr)
        delete VAO;
}

void Brush::Draw(glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, DirectionalLight* sun, std::vector<PointLight*> pointLights)
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

    shader -> setUniform3f("cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    shader -> setUniformMat4("model", &model);
    shader -> setUniformMat4("view", &viewMatrix);
    shader -> setUniformMat4("projection", &projectionMatrix);

    shader -> setUniform3f("material.color", material.color.x, material.color.y, material.color.z);
    shader -> setUniform3f("material.specular", material.specular.x, material.specular.y, material.specular.z);
    shader -> setUniform1i("material.shininess", material.shininess);
    shader -> setUniform1f("material.textureScaleX", material.textureScaleX);
    shader -> setUniform1f("material.textureScaleY", material.textureScaleY);

    shader -> setUniform3f("sun.direction", sun -> getDirection().x, sun -> getDirection().y, sun -> getDirection().z);
    shader -> setUniform3f("sun.color", sun -> getColor().x, sun -> getColor().y, sun -> getColor().z);
    shader -> setUniform3f("sun.ambient", sun -> getAmbient().x, sun -> getAmbient().y, sun -> getAmbient().z);
    shader -> setUniform3f("sun.specular", sun -> getSpecular().x, sun -> getSpecular().y, sun -> getSpecular().z);

    int size = pointLights.size();
    for (int i = 0; i < size; i++)
    {
        PointLight* light = pointLights.at(i);

        std::string temp = "pointLights[" + std::to_string(i) + "]";

        shader -> setUniform3f(temp + ".position", light -> getPosition().x, light -> getPosition().y, light -> getPosition().z);
        shader -> setUniform3f(temp + ".color", light -> getColor().x, light -> getColor().y, light -> getColor().z);
        shader -> setUniform3f(temp + ".specular", light -> getSpecular().x, light -> getSpecular().y, light -> getSpecular().z);
        shader -> setUniform1f(temp + ".constant", light -> getConstant());
        shader -> setUniform1f(temp + ".linear", light -> getLinear());
        shader -> setUniform1f(temp + ".quadratic", light -> getQuadratic());
    }

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

    ErrCheck("Draw");
}

void Brush::Draw(glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
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

    shader -> setUniform3f("cameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

    shader -> setUniformMat4("model", &model);
    shader -> setUniformMat4("view", &viewMatrix);
    shader -> setUniformMat4("projection", &projectionMatrix);

    shader -> setUniform1f("material.textureScaleX", material.textureScaleX);
    shader -> setUniform1f("material.textureScaleY", material.textureScaleY);

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

    ErrCheck("Draw_2");
}
