#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "../../../../Common.h"

#include "../../GameObject.hpp"

class PointLight : public GameObject
{
private:   
    glm::vec3 color;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

public:
    PointLight(float x, float y, float z, float r1, float g1, float b1, float r2, float g2, float b2, float constant, float linear, float quadratic);

    void changeColor(float r, float g, float b) {color = glm::vec3(r, g, b);}

    inline glm::vec3 getColor() {return color;}
    inline glm::vec3 getSpecular() {return specular;}
    inline float getConstant() {return constant;}
    inline float getLinear() {return linear;}
    inline float getQuadratic() {return quadratic;}
};

#endif // POINT_LIGHT_H
