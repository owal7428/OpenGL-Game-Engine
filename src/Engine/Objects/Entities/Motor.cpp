#include "Motor.hpp"

#include "../../../Common.h"
#include "../../Utility/util.h"

Motor::Motor(Brush* brush, float pivot_x, float pivot_y, float pivot_z, int rotation_speed)
{
    this -> brush = brush;

    std::array<float, 3> brushLocation = brush -> getLocation();

    this -> pivot_x = pivot_x;
    this -> pivot_y = pivot_y;
    this -> pivot_z = pivot_z;

    rot_x = brushLocation[0] - pivot_x;
    rot_y = brushLocation[1] - pivot_y;
    rot_z = brushLocation[2] - pivot_z;

    this -> rotation_speed = rotation_speed;
}

void Motor::Act(double deltaTime)
{
    angle += (float) rotation_speed * deltaTime;
    
    while (angle >= 360)
        angle -= 360;
    
    

}
