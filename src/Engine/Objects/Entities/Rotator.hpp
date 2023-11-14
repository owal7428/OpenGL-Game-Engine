#ifndef ROTATOR_H
#define ROTATOR_H

#include "../../../Common.h"

#include "../Brushes/Brush.hpp"

class Rotator
{
private:
    glm::vec3 pivot;
    glm::vec3 axis;

    // This should be in degrees / second
    int rotation_speed;

    Brush* brush;

public:
    /* Constructor given defined spatial axis.
    *  @param pivot World coordinates for point around which rotation should occur.
    *  @param axis World coordinates for axis around which rotation should occur.
    *  @param rotation_speed Angular speed of rotation in degrees per second. */
    Rotator(Brush* brush, int pivot_x, int pivot_y, int pivot_z, 
            int axis_x, int axis_y, int axis_z, int rotation_speed);

    /* Constructor given angles for spatial axis.
    *  @param pivot World coordinates for point around which rotation should occur.
    *  @param theta Rotation of axis in x-z plane in degrees.
    *  @param phi Rotation of axis in y-z plane in degrees. 
    *  @param rotation_speed Angular speed of rotation in degrees per second. */
    Rotator(Brush* brush, int pivot_x, int pivot_y, int pivot_z, 
            int theta, int phi, int rotation_speed);

    /* Externally rotates the object tied to the rotator around the initialized axis.
    *  @param deltaTime Time that has passed since last rotation in seconds. */
    void Rotate(double deltaTime);
};

#endif // ROTATOR_H
