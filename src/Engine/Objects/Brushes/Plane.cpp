#include "Plane.hpp"

#include "../../Utility/util.h"

// Vertex data for star object
static float vertexData[] = 
{
    // Front        // Normals
    -1, -1, 1,      0, 0, 1,  
    1, -1, 1,       0, 0, 1,
    1, 1, 1,        0, 0, 1,
    -1, 1, 1,       0, 0, 1,
};

const int numVertices = 4;

Plane::Plane(const char* textureFile, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    texture = new Texture(textureFile);

    hasTexture = true;

    this -> position    = position;
    this -> rotation    = rotation;
    this -> scale       = scale;
}

Plane::Plane(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
    texture = nullptr;
    
    hasTexture = false;

    this -> position    = position;
    this -> rotation    = rotation;
    this -> scale       = scale;
}

Plane::~Plane()
{
    if (texture != nullptr)
        delete texture;
}

void Plane::Draw(int emission, float shiny)
{
    if (hasTexture)
        drawTextured(emission, shiny);
    else
        drawUntextured(emission, shiny);
}

void Plane::drawTextured(int emission, float shiny)
{
    //  Set specular color to white
    float green[] = {0,1,0,1};
    float white[] = {1,1,1,1};
    float black[] = {0,0,0,1};
    glColor4fv(green);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,black);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,green);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);

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

    glBegin(GL_QUADS);
    
    // Starting address for current face
    int base = 0;
    glColor3f(1,1,1);
    glNormal3f(vertexData[base + 3], vertexData[base + 4], vertexData[base + 5]);
    
    float x1 = vertexData[base + 0];
    float y1 = vertexData[base + 1];
    float z1 = vertexData[base + 2];

    float x2 = vertexData[base + 6 + 0];
    float y2 = vertexData[base + 6 + 1];
    float z2 = vertexData[base + 6 + 2];
    
    float x3 = vertexData[base + 12 + 0];
    float y3 = vertexData[base + 12 + 1];
    float z3 = vertexData[base + 12 + 2];

    float x4 = vertexData[base + 18 + 0];
    float y4 = vertexData[base + 18 + 1];
    float z4 = vertexData[base + 18 + 2];

    glTexCoord2f(0,0); glVertex3f(x1, y1, z1); 
    glTexCoord2f(1,0); glVertex3f(x2, y2, z2); 
    glTexCoord2f(1,1); glVertex3f(x3, y3, z3); 
    glTexCoord2f(0,1); glVertex3f(x4, y4, z4);

    //texture[textureFile] -> Unbind();

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Plane::drawUntextured(int emission, float shiny)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    // Define normals
    glNormalPointer(GL_FLOAT, 6 * sizeof(float), (void*)12);
    glEnableClientState(GL_NORMAL_ARRAY);

    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(rotation[0], 1,0,0);
    glRotatef(rotation[1], 0,1,0);
    glRotatef(rotation[2], 0,0,1);
    glScalef(scale[0], scale[1], scale[2]);
    glDrawArrays(GL_QUADS, 0, numVertices);
    glPopMatrix();

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
