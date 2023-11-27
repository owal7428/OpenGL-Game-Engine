#include "Motor.hpp"

Motor::Motor(Brush* brush, int axis_x, int axis_y, int axis_z, int rotation_speed)
{
    this -> brush = brush;

    axis = glm::vec3((float) axis_x, (float) axis_y, (float) axis_z);

    glm::normalize(axis);

    this -> rotation_speed = rotation_speed;

    this -> angle = 0;
}

Motor::Motor(Brush* brush, int theta, int phi, int rotation_speed)
{
    this -> brush = brush;

    float theta_radians = glm::radians((float) theta);
    float phi_radians   = glm::radians((float) phi);

    // Converts angles in spherical coordinates to unit vector
    float axis_x = glm::cos(theta_radians) * glm::cos(phi_radians);
    float axis_y = glm::sin(phi_radians);
    float axis_z = glm::sin(theta_radians) * glm::cos(phi_radians);

    axis = glm::vec3(axis_x, axis_y, axis_z);

    glm::normalize(axis);

    this -> rotation_speed = rotation_speed;

    this -> angle = 0;
}

void Motor::Spin(double deltaTime)
{   
    angle += (float) rotation_speed * (float) deltaTime;
    
    // % isn't available for floats, so this is next best thing
    while (angle >= 360)
        angle -= 360;
    
    float angleInRadians = glm::radians(angle);
    
    glm::quat newRot = glm::angleAxis(angleInRadians, axis);

    brush -> Rotate(newRot);
}
