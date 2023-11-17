#include "Star.hpp"

#include "../../Utility/util.h"

// Vertex data for star object
static float vertexData[] = 
{
    // Top point                    // Normal vectors                               // Texture coordinates
    0, 0, 0.5,                      -0.75, 0.2724535, 1.22604075,                   0, 0,
    0, 2.25, 0,                     -0.75, 0.2724535, 1.22604075,                   1, 0,
    -0.544907, 0.75, 0,             -0.75, 0.2724535, 1.22604075,                   1, 1,
    0, 0, 0.5,                      0.75, 0.2724535, 1.22604075,                    0, 0,
    0.544907, 0.75, 0,              0.75, 0.2724535, 1.22604075,                    1, 0,
    0, 2.25, 0,                     0.75, 0.2724535, 1.22604075,                    1, 1,

    // Top-right point
    0, 0, 0.5,                      0.0277125, 0.7976465, 1.226671220475,           0, 0,
    2.1402, 0.694575, 0,            0.0277125, 0.7976465, 1.226671220475,           1, 0,
    0.544907, 0.75, 0,              0.0277125, 0.7976465, 1.226671220475,           1, 1,
    0, 0, 0.5,                      0.49068275, -0.6292935, 1.226135377575,         0, 0,
    0.881613, -0.2867905, 0,        0.49068275, -0.6292935, 1.226135377575,         1, 0,
    2.1402, 0.694575, 0,            0.49068275, -0.6292935, 1.226135377575,         1, 1,

    // Bottom-right point
    0, 0, 0.5,                      0.76672975, 0.2204685, 1.225461287475,          0, 0,
    1.32255, -1.82025, 0,           0.76672975, 0.2204685, 1.225461287475,          1, 0,
    0.881613, -0.2867905, 0,        0.76672975, 0.2204685, 1.225461287475,          1, 1,
    0, 0, 0.5,                      -0.446602, -0.661275, 1.2260646873,             0, 0,
    0, -0.927046, 0,                -0.446602, -0.661275, 1.2260646873,             1, 0,
    1.32255, -1.82025, 0,           -0.446602, -0.661275, 1.2260646873,             1, 1,

    // Bottom-left point
    0, 0, 0.5,                      0.446602, -0.661275, 1.2260646873,              0, 0,
    -1.32255, -1.82025, 0,          0.446602, -0.661275, 1.2260646873,              1, 0,
    0, -0.927046, 0,                0.446602, -0.661275, 1.2260646873,              1, 1,
    0, 0, 0.5,                      -0.76672975, 0.2204685, 1.225461287475,         0, 0,
    -0.881613, -0.2867905, 0,       -0.76672975, 0.2204685, 1.225461287475,         1, 0,
    -1.32255, -1.82025, 0,          -0.76672975, 0.2204685, 1.225461287475,         1, 1,

    // Top-left
    0, 0, 0.5,                      -0.49068275, -0.6292935, 1.226135377575,        0, 0,
    -2.1402, 0.694575, 0,           -0.49068275, -0.6292935, 1.226135377575,        1, 0,
    -0.881613, -0.2867905, 0,       -0.49068275, -0.6292935, 1.226135377575,        1, 1,
    0, 0, 0.5,                      -0.0277125, 0.7976465, 1.226671220475,          0, 0,
    -0.544907, 0.75, 0,             -0.0277125, 0.7976465, 1.226671220475,          1, 0,
    -2.1402, 0.694575, 0,           -0.0277125, 0.7976465, 1.226671220475,          1, 1,

    // These points are for the back side

    // Top point                    // Normals
    0, 0, -0.5,                     -0.75, 0.2724535, -1.22604075,                  0, 0,
    -0.544907, 0.75, 0,             -0.75, 0.2724535, -1.22604075,                  1, 0,
    0, 2.25, 0,                     -0.75, 0.2724535, -1.22604075,                  1, 1,
    0, 0, -0.5,                     0.75, 0.2724535, -1.22604075,                   0, 0,
    0, 2.25, 0,                     0.75, 0.2724535, -1.22604075,                   1, 0,
    0.544907, 0.75, 0,              0.75, 0.2724535, -1.22604075,                   1, 1,

    // Top-right point
    0, 0, -0.5,                     0.0277125, 0.7976465, -1.226671220475,          0, 0,
    0.544907, 0.75, 0,              0.0277125, 0.7976465, -1.226671220475,          1, 0,
    2.1402, 0.694575, 0,            0.0277125, 0.7976465, -1.226671220475,          1, 1,
    0, 0, -0.5,                     0.49068275, -0.6292935, -1.226135377575,        0, 0,
    2.1402, 0.694575, 0,            0.49068275, -0.6292935, -1.226135377575,        1, 0,
    0.881613, -0.2867905, 0,        0.49068275, -0.6292935, -1.226135377575,        1, 1,

    // Bottom-right point
    0, 0, -0.5,                     0.76672975, 0.2204685, -1.225461287475,         0, 0,
    0.881613, -0.2867905, 0,        0.76672975, 0.2204685, -1.225461287475,         1, 0,
    1.32255, -1.82025, 0,           0.76672975, 0.2204685, -1.225461287475,         1, 1,
    0, 0, -0.5,                     -0.446602, -0.661275, -1.2260646873,            0, 0,
    1.32255, -1.82025, 0,           -0.446602, -0.661275, -1.2260646873,            1, 0,
    0, -0.927046, 0,                -0.446602, -0.661275, -1.2260646873,            1, 1,

    // Bottom-left point
    0, 0, -0.5,                     0.446602, -0.661275, -1.2260646873,             0, 0,
    0, -0.927046, 0,                0.446602, -0.661275, -1.2260646873,             1, 0,
    -1.32255, -1.82025, 0,          0.446602, -0.661275, -1.2260646873,             1, 1,
    0, 0, -0.5,                     -0.76672975, 0.2204685, -1.225461287475,        0, 0,
    -1.32255, -1.82025, 0,          -0.76672975, 0.2204685, -1.225461287475,        1, 0,
    -0.881613, -0.2867905, 0,       -0.76672975, 0.2204685, -1.225461287475,        1, 1,

    // Top-left
    0, 0, -0.5,                     -0.49068275, -0.6292935, -1.226135377575,       0, 0,
    -0.881613, -0.2867905, 0,       -0.49068275, -0.6292935, -1.226135377575,       1, 0,
    -2.1402, 0.694575, 0,           -0.49068275, -0.6292935, -1.226135377575,       1, 1,
    0, 0, -0.5,                     -0.0277125, 0.7976465, -1.226671220475,         0, 0,
    -2.1402, 0.694575, 0,           -0.0277125, 0.7976465, -1.226671220475,         1, 0,
    -0.544907, 0.75, 0,             -0.0277125, 0.7976465, -1.226671220475,         1, 1,
};

const int numVertices = 64;

Star::Star(const char* textureFile,
           float x, float y, float z,
           float rot_x, float rot_y, float rot_z,
           float scale_x, float scale_y, float scale_z) : Brush(textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    // Do nothing for now
}

Star::Star(float x, float y, float z,
           float rot_x, float rot_y, float rot_z,
           float scale_x, float scale_y, float scale_z) : Brush(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    // Do nothing for now
}

void Star::Draw(int emission, float shiny)
{
    float color_array[] = {color.x, color.y, color.z, 1};
    float black[] = {0, 0, 0, 1};
    
    glColor4fv(color_array);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, black);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, color_array);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, color_array);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shiny);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Define normals
    glNormalPointer(GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableClientState(GL_NORMAL_ARRAY);

    // Define texture coordinates
    glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    if (hasTexture)
    {
        //  Enable textures
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

        texture -> Bind();
    }
    
    if (drawWireFrame)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDisable(GL_LIGHTING);
    }

    glPushMatrix();

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, position);

    glm::mat4 model = glm::mat4(1.0f);
    model = model * glm::toMat4(externalRotations * rotation);
    model = glm::scale(model, scale);
    
    glMultMatrixf(glm::value_ptr(view * model));

    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    
    glPopMatrix();

    if (drawWireFrame)
    {
        glEnable(GL_LIGHTING);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    if (hasTexture)
    {
        texture -> Unbind();
        glDisable(GL_TEXTURE_2D);
    }

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
