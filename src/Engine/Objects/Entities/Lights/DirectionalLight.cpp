#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(float x, float y, float z, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3)
{
    this -> direction = glm::vec3(x,y,z);
    this -> color = glm::vec3(r1,g1,b1);
    this -> ambient = glm::vec3(r2,g2,b2);
    this -> specular = glm::vec3(r3,g3,b3);
}
