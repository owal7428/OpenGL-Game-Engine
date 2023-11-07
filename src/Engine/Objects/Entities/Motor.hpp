#ifndef MOTOR_H
#define MOTOR_H

#include "../Brushes/Brush.hpp"

class Motor
{
private:
    float pivot_x; float pivot_y; float pivot_z;
    float rot_x; float rot_y; float rot_z;
    float angle;

    // This should be in degrees / second
    int rotation_speed;

    Brush* brush;

public:
    Motor(Brush* brush, float pivot_x, float pivot_y, float pivot_z, int rotation_speed);
    //~Motor();

    void Act(double deltaTime);
};

#endif // MOTOR_H
