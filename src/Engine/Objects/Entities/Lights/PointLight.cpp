#include "PointLight.hpp"

PointLight::PointLight(float x, float y, float z, float r1, float g1, float b1, float r2, float g2, float b2, float constant, float linear, float quadratic)
{
    this -> position = glm::vec3(x, y, z);
    this -> color = glm::vec3(r1, g1, b1);
    this -> specular = glm::vec3(r2, g2, b2);

    this -> constant = constant;
    this -> linear = linear;
    this -> quadratic = quadratic;
}
