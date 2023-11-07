#include "Star.hpp"

#include "../../Utility/util.h"

// Vertex data for star object
static float vertexData[] = 
{
    // Top point                // RGB colors       // Normal vectors
    0, 0, 0.5,                1, 0, 0,            -0.75, 0.2724535, 1.22604075,
    0, 2.25, 0,                 1, 0, 0,            -0.75, 0.2724535, 1.22604075,
    -0.544907, 0.75, 0,         1, 0, 0,            -0.75, 0.2724535, 1.22604075,  
    0, 0, 0.5,                1, 1, 0,            0.75, 0.2724535, 1.22604075,
    0.544907, 0.75, 0,          1, 1, 0,            0.75, 0.2724535, 1.22604075,
    0, 2.25, 0,                 1, 1, 0,            0.75, 0.2724535, 1.22604075,

    // Top-right point
    0, 0, 0.5,                0, 1, 0,            0.0277125, 0.7976465, 1.226671220475,
    2.1402, 0.694575, 0,        0, 1, 0,            0.0277125, 0.7976465, 1.226671220475,
    0.544907, 0.75, 0,          0, 1, 0,            0.0277125, 0.7976465, 1.226671220475,
    0, 0, 0.5,                0, 1, 1,            0.49068275, -0.6292935, 1.226135377575,
    0.881613, -0.2867905, 0,    0, 1, 1,            0.49068275, -0.6292935, 1.226135377575,
    2.1402, 0.694575, 0,        0, 1, 1,            0.49068275, -0.6292935, 1.226135377575,

    // Bottom-right point
    0, 0, 0.5,                0, 0, 1,            0.76672975, 0.2204685, 1.225461287475,
    1.32255, -1.82025, 0,       0, 0, 1,            0.76672975, 0.2204685, 1.225461287475,
    0.881613, -0.2867905, 0,    0, 0, 1,            0.76672975, 0.2204685, 1.225461287475,
    0, 0, 0.5,                1, 0, 1,            -0.446602, -0.661275, 1.2260646873,
    0, -0.927046, 0,            1, 0, 1,            -0.446602, -0.661275, 1.2260646873,
    1.32255, -1.82025, 0,       1, 0, 1,            -0.446602, -0.661275, 1.2260646873,

    // Bottom-left point
    0, 0, 0.5,                1, 0.5, 1,          0.446602, -0.661275, 1.2260646873,
    -1.32255, -1.82025, 0,      1, 0.5, 1,          0.446602, -0.661275, 1.2260646873,
    0, -0.927046, 0,            1, 0.5, 1,          0.446602, -0.661275, 1.2260646873,
    0, 0, 0.5,                1, 1, 1,            -0.76672975, 0.2204685, 1.225461287475,
    -0.881613, -0.2867905, 0,   1, 1, 1,            -0.76672975, 0.2204685, 1.225461287475,
    -1.32255, -1.82025, 0,      1, 1, 1,            -0.76672975, 0.2204685, 1.225461287475,

    // Top-left
    0, 0, 0.5,                0.75, 0.25, 1,      -0.49068275, -0.6292935, 1.226135377575,
    -2.1402, 0.694575, 0,       0.75, 0.25, 1,      -0.49068275, -0.6292935, 1.226135377575,
    -0.881613, -0.2867905, 0,   0.75, 0.25, 1,      -0.49068275, -0.6292935, 1.226135377575,
    0, 0, 0.5,                0.5, 0.5, 1,        -0.0277125, 0.7976465, 1.226671220475,
    -0.544907, 0.75, 0,         0.5, 0.5, 1,        -0.0277125, 0.7976465, 1.226671220475,
    -2.1402, 0.694575, 0,       0.5, 0.5, 1,        -0.0277125, 0.7976465, 1.226671220475,

    // These points are for the back side

    // Top point                // RGB colors       // Normals
    0, 0, -0.5,               1, 0, 0,            -0.75, 0.2724535, -1.22604075,
    -0.544907, 0.75, 0,         1, 0, 0,            -0.75, 0.2724535, -1.22604075,       
    0, 2.25, 0,                 1, 0, 0,            -0.75, 0.2724535, -1.22604075,
    0, 0, -0.5,               1, 1, 0,            0.75, 0.2724535, -1.22604075,
    0, 2.25, 0,                 1, 1, 0,            0.75, 0.2724535, -1.22604075,
    0.544907, 0.75, 0,          1, 1, 0,            0.75, 0.2724535, -1.22604075,

    // Top-right point
    0, 0, -0.5,               0, 1, 0,            0.0277125, 0.7976465, -1.226671220475,
    0.544907, 0.75, 0,          0, 1, 0,            0.0277125, 0.7976465, -1.226671220475,
    2.1402, 0.694575, 0,        0, 1, 0,            0.0277125, 0.7976465, -1.226671220475,
    0, 0, -0.5,               0, 1, 1,            0.49068275, -0.6292935, -1.226135377575,
    2.1402, 0.694575, 0,        0, 1, 1,            0.49068275, -0.6292935, -1.226135377575,
    0.881613, -0.2867905, 0,    0, 1, 1,            0.49068275, -0.6292935, -1.226135377575,

    // Bottom-right point
    0, 0, -0.5,               0, 0, 1,            0.76672975, 0.2204685, -1.225461287475,
    0.881613, -0.2867905, 0,    0, 0, 1,            0.76672975, 0.2204685, -1.225461287475,
    1.32255, -1.82025, 0,       0, 0, 1,            0.76672975, 0.2204685, -1.225461287475,
    0, 0, -0.5,               1, 0, 1,            -0.446602, -0.661275, -1.2260646873,
    1.32255, -1.82025, 0,       1, 0, 1,            -0.446602, -0.661275, -1.2260646873,
    0, -0.927046, 0,            1, 0, 1,            -0.446602, -0.661275, -1.2260646873,

    // Bottom-left point
    0, 0, -0.5,               1, 0.5, 1,          0.446602, -0.661275, -1.2260646873,
    0, -0.927046, 0,            1, 0.5, 1,          0.446602, -0.661275, -1.2260646873,
    -1.32255, -1.82025, 0,      1, 0.5, 1,          0.446602, -0.661275, -1.2260646873,
    0, 0, -0.5,               1, 1, 1,            -0.76672975, 0.2204685, -1.225461287475,
    -1.32255, -1.82025, 0,      1, 1, 1,            -0.76672975, 0.2204685, -1.225461287475,
    -0.881613, -0.2867905, 0,   1, 1, 1,            -0.76672975, 0.2204685, -1.225461287475,

    // Top-left
    0, 0, -0.5,               0.75, 0.25, 1,      -0.49068275, -0.6292935, -1.226135377575,
    -0.881613, -0.2867905, 0,   0.75, 0.25, 1,      -0.49068275, -0.6292935, -1.226135377575,
    -2.1402, 0.694575, 0,       0.75, 0.25, 1,      -0.49068275, -0.6292935, -1.226135377575,
    0, 0, -0.5,               0.5, 0.5, 1,        -0.0277125, 0.7976465, -1.226671220475,
    -2.1402, 0.694575, 0,       0.5, 0.5, 1,        -0.0277125, 0.7976465, -1.226671220475,
    -0.544907, 0.75, 0,         0.5, 0.5, 1,        -0.0277125, 0.7976465, -1.226671220475,
};

const int numVertices = 64;

Star::Star(const char* textureFile, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    texture = new Texture(textureFile);

    hasTexture = true;

    this -> position    = position;
    this -> rotation    = rotation;
    this -> scale       = scale;
}

Star::Star(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    texture = nullptr;
    
    hasTexture = false;

    this -> position    = position;
    this -> rotation    = rotation;
    this -> scale       = scale;
}

Star::~Star()
{
    if (texture != nullptr)
        delete texture;
}

void Star::Draw(int emission, float shiny)
{
    if (hasTexture)
        drawTextured(emission, shiny);
    else
        drawUntextured(emission, shiny);
}

void Star::drawTextured(int emission, float shiny)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float Emission[]  = {0.0f,0.0f,0.01f*emission,1.0f};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

    glPushMatrix();
    
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(rotation[0], 1,0,0);
    glRotatef(rotation[1], 0,1,0);
    glRotatef(rotation[2], 0,0,1);
    glScalef(scale[0], scale[1], scale[2]);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    texture -> Bind();

    glBegin(GL_TRIANGLES);
    
    // Read info from vertexData to actually draw
    for (int i = 0; i < 20; i++) 
    {
        // Starting address for current face
        int base = 27 * i;
        //glColor3f(vertexData[base + 3], vertexData[base + 4], vertexData[base + 5]);
        glColor3f(1,1,1);
        glNormal3f(vertexData[base + 6], vertexData[base + 7], vertexData[base + 8]);

        float x1 = vertexData[base + 0];
        float y1 = vertexData[base + 1];
        float z1 = vertexData[base + 2];

        float x2 = vertexData[base + 9 + 0];
        float y2 = vertexData[base + 9 + 1];
        float z2 = vertexData[base + 9 + 2];
        
        float x3 = vertexData[base + 18 + 0];
        float y3 = vertexData[base + 18 + 1];
        float z3 = vertexData[base + 18 + 2];

        glTexCoord2f(0,0); glVertex3f(x1, y1, z1); 
        glTexCoord2f(1,0); glVertex3f(x2, y2, z2); 
        glTexCoord2f(1,1); glVertex3f(x3, y3, z3); 
    }

    glEnd();

    //texture.Unbind();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Star::drawUntextured(int emission, float shiny)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 9 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    //  Define colors for each vertex
    glColorPointer(3,GL_FLOAT, 9 * sizeof(float), (void*)12);
    glEnableClientState(GL_COLOR_ARRAY);
    // Define normal vector for each vertex
    glNormalPointer(GL_FLOAT, 9 * sizeof(float), (void*)24);
    glEnableClientState(GL_NORMAL_ARRAY);

    //  Set specular color to white
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(rotation[0], 1,0,0);
    glRotatef(rotation[1], 0,1,0);
    glRotatef(rotation[2], 0,0,1);
    glScalef(scale[0], scale[1], scale[2]);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glPopMatrix();

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);
    //  Disable color array
    glDisableClientState(GL_COLOR_ARRAY);
    // Disable normal array
    glDisableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
