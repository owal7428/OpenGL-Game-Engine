#include "Rotator.hpp"

Rotator::Rotator(Brush* brush, int pivot_x, int pivot_y, int pivot_z, 
                 int axis_x, int axis_y, int axis_z, int rotation_speed)
{
    this -> brush = brush;

    pivot = glm::vec3((float) pivot_x, (float) pivot_y, (float) pivot_z);

    axis = glm::vec3((float) axis_x, (float) axis_y, (float) axis_z);

    glm::normalize(axis);

    this -> rotation_speed = rotation_speed;
}

Rotator::Rotator(Brush* brush, int pivot_x, int pivot_y, int pivot_z, 
                 int theta, int phi, int rotation_speed)
{
    this -> brush = brush;

    pivot = glm::vec3((float) pivot_x, (float) pivot_y, (float) pivot_z);

    float theta_radians = glm::radians((float) theta);
    float phi_radians   = glm::radians((float) phi);

    // Converts angles in spherical coordinates to unit vector
    float axis_x = glm::cos(theta_radians) * glm::cos(phi_radians);
    float axis_y = glm::sin(phi_radians);
    float axis_z = glm::sin(theta_radians) * glm::cos(phi_radians);

    axis = glm::vec3(axis_x, axis_y, axis_z);

    glm::normalize(axis);

    this -> rotation_speed = rotation_speed;
}

void Rotator::Rotate(double deltaTime)
{   
    float angle = (float) rotation_speed * (float) deltaTime;
    
    // % isn't available for floats, so this is next best thing
    while (angle >= 360)
        angle -= 360;
    
    float angleInRadians = glm::radians(angle);
    
    // Generate matrices
    
    glm::vec4 position = glm::vec4(brush -> getPosition(), 1);

    glm::mat4 matrix = glm::mat4(1.0f);

    // Translate to origin, rotate, then translate back to correct position
    matrix = glm::translate(matrix, pivot);
    matrix = glm::rotate(matrix, angleInRadians, axis);
    matrix = glm::translate(matrix, glm::vec3(-pivot.x, -pivot.y, -pivot.z));

    position = matrix * position;

    brush -> Move(glm::vec3(position.x, position.y, position.z));
}
