#ifndef DIRECTIONAL_LIGHT_H
#define DIRECTIONAL_LIGHT_H

#include "../../../../Common.h"

#include "../../GameObject.hpp"

class DirectionalLight : public GameObject
{
private:
    glm::vec3 direction;

    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 specular;

public:
    /* Constructor for directional light.
    *  @param rgb1 color of the light.
    *  @param rgb2 color of ambient light.
    *  @param rgb3 color of specular light. */
    DirectionalLight(float x, float y, float z, float r1, float g1, float b1, float r2, float g2, float b2, float r3, float g3, float b3);

    void changeColor(float r, float g, float b) {color = glm::vec3(r, g, b);}

    void setDirection(float x, float y, float z) {direction = glm::vec3(x,y,z);}

    inline glm::vec3 getDirection() {return direction;}
    inline glm::vec3 getColor() {return color;}
    inline glm::vec3 getAmbient() {return ambient;}
    inline glm::vec3 getSpecular() {return specular;}
};

#endif // DIRECTIONAL_LIGHT_H
