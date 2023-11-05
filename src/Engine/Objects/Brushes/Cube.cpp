#include "Cube.hpp"

#include "../../Utility/util.h"

// Vertex data for star object
static float vertexData[] = 
{
    // Front        // Normals
    -1, -1, 1,      0, 0, 1,  
    1, -1, 1,       0, 0, 1,
    1, 1, 1,        0, 0, 1,
    -1, 1, 1,       0, 0, 1,

    //  Back
    1, -1, -1,      0, 0, -1,
    -1, -1, -1,     0, 0, -1,
    -1, 1, -1,      0, 0, -1,
    1, 1, -1,       0, 0, -1,
    
    //  Left
    -1, -1, -1,     -1, 0, 0,
    -1, -1, 1,      -1, 0, 0,
    -1, 1, 1,       -1, 0, 0,
    -1, 1, -1,      -1, 0, 0,

    //  Right
    1, -1, 1,       1, 0, 0,
    1, -1, -1,      1, 0, 0,
    1, 1, -1,       1, 0, 0,
    1, 1, 1,        1, 0, 0,
    
    //  Top
    -1, 1, 1,       0, 1, 0,
    1, 1, 1,        0, 1, 0,
    1, 1, -1,       0, 1, 0,
    -1, 1, -1,      0, 1, 0,

    //  Bottom
    -1, -1, -1,     0, -1, 0,
    1, -1, -1,      0, -1, 0,
    1, -1, 1,       0, -1, 0,
    -1, -1, 1,      0, -1, 0,
};

const int numVertices = 24;

Cube::Cube(const char* textureFiles[6], float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze)
{
    for (int i = 0; i < 6; i++)
    {
        textures[i] = new Texture(textureFiles[i]);
    }

    hasTexture = true;

    this -> x = x;
    this -> y = y;
    this -> z = z;

    this -> scale_x = scale_x;
    this -> scale_y = scale_y;
    this -> scale_z = scale_z;

    this -> th = th;
    this -> ph = ph;
    this -> ze = ze;
}

Cube::Cube(float x, float y, float z,
         float scale_x, float scale_y, float scale_z,
         float th, float ph, float ze)
{
    for (int i = 0; i < 6; i++)
    {
        textures[i] = nullptr;
    }
    
    hasTexture = false;

    this -> x = x;
    this -> y = y;
    this -> z = z;

    this -> scale_x = scale_x;
    this -> scale_y = scale_y;
    this -> scale_z = scale_z;

    this -> th = th;
    this -> ph = ph;
    this -> ze = ze;
}

Cube::~Cube()
{
    for (int i = 0; i < 6; i++)
    {
    if (textures[i] != nullptr)
        delete textures[i];
    }
}

void Cube::Draw(int emission, float shiny)
{
    if (hasTexture)
        drawTextured(emission, shiny);
    else
        drawUntextured(emission, shiny);
}

void Cube::drawTextured(int emission, float shiny)
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

    glTranslatef(x,y,z);
    glRotatef(th, 1,0,0);
    glRotatef(ph, 0,1,0);
    glRotatef(ze, 0,0,1);
    glScalef(scale_x,scale_y,scale_z);

        //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    
    // Read info from vertexData to actually draw
    for (int i = 0; i < 6; i++) 
    {
        textures[i] -> Bind();

        glBegin(GL_QUADS);

        // Starting address for current face
        int base = 24 * i;
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
        
        glEnd();

        textures[i] -> Unbind();
    }

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void Cube::drawUntextured(int emission, float shiny)
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
    glTranslatef(x,y,z);
    glRotatef(th, 1,0,0);
    glRotatef(ph, 0,1,0);
    glRotatef(ze, 0,0,1);
    glScalef(scale_x,scale_y,scale_z);
    glDrawArrays(GL_QUADS, 0, numVertices);
    glPopMatrix();

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
