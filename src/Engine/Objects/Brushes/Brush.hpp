#ifndef BRUSH_H
#define BRUSH_H

#include "../../../Common.h"

class Brush
{
protected:
    bool hasTexture;
    float x, y, z, scale_x, scale_y, scale_z, th, ph, ze;
public:
    Brush() {}

    inline void Move(float x_new, float y_new, float z_new) {x = x_new; y = y_new; z = z_new;}

    inline std::array<float, 3> getLocation() 
    {
        std::array<float, 3> location;
        location[0] = x;
        location[1] = y;
        location[2] = z;

        return location;
    }
};

#endif // BRUSH_H
