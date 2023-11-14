#ifndef MOTOR_H
#define MOTOR_H

#include "../../../Common.h"

#include "../Brushes/Brush.hpp"

class Motor
{
private:
    glm::vec3 axis;
    float angle;

    // This should be in degrees / second
    int rotation_speed;

    Brush* brush;

public:
    /* Constructor given defined spatial axis.
    *  @param axis_x World x coordinates for axis.
    *  @param axis_y World y coordinates for axis.
    *  @param axis_z World z coordinates for axis.
    *  @param rotation_speed Angular speed of rotation in degrees per second. */
    Motor(Brush* brush, int axis_x, int axis_y, int axis_z, int rotation_speed);

    /* Constructor given angles for spatial axis.
    *  @param theta Rotation of axis in x-z plane in degrees.
    *  @param phi Rotation of axis in y-z plane in degrees. 
    *  @param rotation_speed Angular speed of rotation in degrees per second. */
    Motor(Brush* brush, int theta, int phi, int rotation_speed);

    /* Internally rotates the object tied to the motor around the initialized axis.
    *  @param deltaTime Time that has passed since last rotation in seconds. */
    void Spin(double deltaTime);
};

#endif // MOTOR_H
