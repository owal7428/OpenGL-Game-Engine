#include "Engine/Window.hpp"
#include "Engine/Utility/util.h"

#define WOOD 0
#define STEEL 1
#define WATER 2

#define SKYBOX_LEFT 0
#define SKYBOX_FRONT 1
#define SKYBOX_RIGHT 2
#define SKYBOX_BACK 3
#define SKYBOX_TOP 4
#define SKYBOX_BOTTOM 5

int th=0;         //  Angle in x-y plane
int ph=0;         //  Angle in y-z plane

int x_rot_time=0;
int y_rot_time=0;
int z_rot_time=0;

// Current states of the arrow keys
int leftKeyDown = 0;
int rightKeyDown = 0;
int upKeyDown = 0;
int downKeyDown = 0;

// Current states of the wasd keys
int wKeyDown = 0;
int aKeyDown = 0;
int sKeyDown = 0;
int dKeyDown = 0;

int spaceKeyToggle = 0;

double asp = 1;
int fov = 90;
int mode = 0;

double xPos = 0;
double yPos = 0;
double zPos = 0;

double xOffset = 0;
double yOffset = 0;
double zOffset = 1;

// Light values taken from ex13.c
int light     =   1;  // Lighting
int distance  =   5;  // Light distance
int inc       =  10;  // Ball increment
int smooth    =   1;  // Smooth/Flat shading
int local     =   0;  // Local Viewer Model
int ambient   =   5;  // Ambient intensity (%)
int diffuse   =  50;  // Diffuse intensity (%)
int specular  =   20;  // Specular intensity (%)
int emission  =   0;  // Emission intensity (%)
int shininess =   1;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light

int objectMode = 0;

unsigned int texture[3];
unsigned int skybox[6];

const float depth = 0.5;

float vertexData[] = 
{
    // Top point                // RGB colors       // Normal vectors
    0, 0, depth,                1, 0, 0,            -0.75, 0.2724535, 1.22604075,
    0, 2.25, 0,                 1, 0, 0,            -0.75, 0.2724535, 1.22604075,
    -0.544907, 0.75, 0,         1, 0, 0,            -0.75, 0.2724535, 1.22604075,  
    0, 0, depth,                1, 1, 0,            0.75, 0.2724535, 1.22604075,
    0.544907, 0.75, 0,          1, 1, 0,            0.75, 0.2724535, 1.22604075,
    0, 2.25, 0,                 1, 1, 0,            0.75, 0.2724535, 1.22604075,

    // Top-right point
    0, 0, depth,                0, 1, 0,            0.0277125, 0.7976465, 1.226671220475,
    2.1402, 0.694575, 0,        0, 1, 0,            0.0277125, 0.7976465, 1.226671220475,
    0.544907, 0.75, 0,          0, 1, 0,            0.0277125, 0.7976465, 1.226671220475,
    0, 0, depth,                0, 1, 1,            0.49068275, -0.6292935, 1.226135377575,
    0.881613, -0.2867905, 0,    0, 1, 1,            0.49068275, -0.6292935, 1.226135377575,
    2.1402, 0.694575, 0,        0, 1, 1,            0.49068275, -0.6292935, 1.226135377575,

    // Bottom-right point
    0, 0, depth,                0, 0, 1,            0.76672975, 0.2204685, 1.225461287475,
    1.32255, -1.82025, 0,       0, 0, 1,            0.76672975, 0.2204685, 1.225461287475,
    0.881613, -0.2867905, 0,    0, 0, 1,            0.76672975, 0.2204685, 1.225461287475,
    0, 0, depth,                1, 0, 1,            -0.446602, -0.661275, 1.2260646873,
    0, -0.927046, 0,            1, 0, 1,            -0.446602, -0.661275, 1.2260646873,
    1.32255, -1.82025, 0,       1, 0, 1,            -0.446602, -0.661275, 1.2260646873,

    // Bottom-left point
    0, 0, depth,                1, 0.5, 1,          0.446602, -0.661275, 1.2260646873,
    -1.32255, -1.82025, 0,      1, 0.5, 1,          0.446602, -0.661275, 1.2260646873,
    0, -0.927046, 0,            1, 0.5, 1,          0.446602, -0.661275, 1.2260646873,
    0, 0, depth,                1, 1, 1,            -0.76672975, 0.2204685, 1.225461287475,
    -0.881613, -0.2867905, 0,   1, 1, 1,            -0.76672975, 0.2204685, 1.225461287475,
    -1.32255, -1.82025, 0,      1, 1, 1,            -0.76672975, 0.2204685, 1.225461287475,

    // Top-left
    0, 0, depth,                0.75, 0.25, 1,      -0.49068275, -0.6292935, 1.226135377575,
    -2.1402, 0.694575, 0,       0.75, 0.25, 1,      -0.49068275, -0.6292935, 1.226135377575,
    -0.881613, -0.2867905, 0,   0.75, 0.25, 1,      -0.49068275, -0.6292935, 1.226135377575,
    0, 0, depth,                0.5, 0.5, 1,        -0.0277125, 0.7976465, 1.226671220475,
    -0.544907, 0.75, 0,         0.5, 0.5, 1,        -0.0277125, 0.7976465, 1.226671220475,
    -2.1402, 0.694575, 0,       0.5, 0.5, 1,        -0.0277125, 0.7976465, 1.226671220475,

    // These points are for the back side

    // Top point                // RGB colors       // Normals
    0, 0, -depth,               1, 0, 0,            -0.75, 0.2724535, -1.22604075,
    -0.544907, 0.75, 0,         1, 0, 0,            -0.75, 0.2724535, -1.22604075,       
    0, 2.25, 0,                 1, 0, 0,            -0.75, 0.2724535, -1.22604075,
    0, 0, -depth,               1, 1, 0,            0.75, 0.2724535, -1.22604075,
    0, 2.25, 0,                 1, 1, 0,            0.75, 0.2724535, -1.22604075,
    0.544907, 0.75, 0,          1, 1, 0,            0.75, 0.2724535, -1.22604075,

    // Top-right point
    0, 0, -depth,               0, 1, 0,            0.0277125, 0.7976465, -1.226671220475,
    0.544907, 0.75, 0,          0, 1, 0,            0.0277125, 0.7976465, -1.226671220475,
    2.1402, 0.694575, 0,        0, 1, 0,            0.0277125, 0.7976465, -1.226671220475,
    0, 0, -depth,               0, 1, 1,            0.49068275, -0.6292935, -1.226135377575,
    2.1402, 0.694575, 0,        0, 1, 1,            0.49068275, -0.6292935, -1.226135377575,
    0.881613, -0.2867905, 0,    0, 1, 1,            0.49068275, -0.6292935, -1.226135377575,

    // Bottom-right point
    0, 0, -depth,               0, 0, 1,            0.76672975, 0.2204685, -1.225461287475,
    0.881613, -0.2867905, 0,    0, 0, 1,            0.76672975, 0.2204685, -1.225461287475,
    1.32255, -1.82025, 0,       0, 0, 1,            0.76672975, 0.2204685, -1.225461287475,
    0, 0, -depth,               1, 0, 1,            -0.446602, -0.661275, -1.2260646873,
    1.32255, -1.82025, 0,       1, 0, 1,            -0.446602, -0.661275, -1.2260646873,
    0, -0.927046, 0,            1, 0, 1,            -0.446602, -0.661275, -1.2260646873,

    // Bottom-left point
    0, 0, -depth,               1, 0.5, 1,          0.446602, -0.661275, -1.2260646873,
    0, -0.927046, 0,            1, 0.5, 1,          0.446602, -0.661275, -1.2260646873,
    -1.32255, -1.82025, 0,      1, 0.5, 1,          0.446602, -0.661275, -1.2260646873,
    0, 0, -depth,               1, 1, 1,            -0.76672975, 0.2204685, -1.225461287475,
    -1.32255, -1.82025, 0,      1, 1, 1,            -0.76672975, 0.2204685, -1.225461287475,
    -0.881613, -0.2867905, 0,   1, 1, 1,            -0.76672975, 0.2204685, -1.225461287475,

    // Top-left
    0, 0, -depth,               0.75, 0.25, 1,      -0.49068275, -0.6292935, -1.226135377575,
    -0.881613, -0.2867905, 0,   0.75, 0.25, 1,      -0.49068275, -0.6292935, -1.226135377575,
    -2.1402, 0.694575, 0,       0.75, 0.25, 1,      -0.49068275, -0.6292935, -1.226135377575,
    0, 0, -depth,               0.5, 0.5, 1,        -0.0277125, 0.7976465, -1.226671220475,
    -2.1402, 0.694575, 0,       0.5, 0.5, 1,        -0.0277125, 0.7976465, -1.226671220475,
    -0.544907, 0.75, 0,         0.5, 0.5, 1,        -0.0277125, 0.7976465, -1.226671220475,
};

const int numVertices = 64;

void drawStar(float x, float y, float z, float scale_x, float scale_y, float scale_z, float th, float ph, float ze)
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
    glTranslatef(x,y,z);
    glRotatef(th, 1,0,0);
    glRotatef(ph, 0,1,0);
    glRotatef(ze, 0,0,1);
    glScalef(scale_x,scale_y,scale_z);
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

void drawStar_Textured(int textureFile, float x, float y, float z, float scale_x, float scale_y, float scale_z, float th, float ph, float ze)
{
    //  Set specular color to white
    float white[] = {1,1,1,1};
    float Emission[]  = {0.0f,0.0f,0.01f*emission,1.0f};
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

    glPushMatrix();
    
    glTranslatef(x,y,z);
    glRotatef(th, 1,0,0);
    glRotatef(ph, 0,1,0);
    glRotatef(ze, 0,0,1);
    glScalef(scale_x,scale_y,scale_z);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
    glBindTexture(GL_TEXTURE_2D,texture[textureFile]);

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
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

float cubeVertexData[] = 
{
    // Front edges
    1, -1, 1, 
    -1, -1, 1,
    -1, -1, 1, 
    -1, 1, 1,
    -1, 1, 1, 
    1, 1, 1,
    1, 1, 1, 
    1, -1, 1,

    // Side edges
    1, -1, 1, 
    1, -1, -1,
    -1, -1, 1, 
    -1, -1, -1,
    -1, 1, 1, 
    -1, 1, -1,
    1, 1, 1, 
    1, 1, -1,

    // Back face edges
    1, -1, -1, 
    -1, -1, -1,
    -1, -1, -1, 
    -1, 1, -1,
    -1, 1, -1, 
    1, 1, -1,
    1, 1, -1, 
    1, -1, -1,
};

void drawWiredCube(float x, float y, float z, float scale_x, float scale_y, float scale_z, float th, float ph, float ze)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertexData), cubeVertexData, GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 3 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(x,y,z);
    glRotatef(th, 1,0,0);
    glRotatef(ph, 0,1,0);
    glRotatef(ze, 0,0,1);
    glScalef(scale_x,scale_y,scale_z);
    glDrawArrays(GL_LINES, 0, 24);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

float rhombusVertexData[] =
{
    // Front face   // Normals
    -1, -1, -1,     0, -1, 1,
    1, -1, -1,      0, -1, 1,
    1, 1, 1,        0, -1, 1,
    -1, 1, 1,       0, -1, 1,

    //  Back face
    1, -1, -3,      0, 1, -1,
    -1, -1, -3,     0, 1, -1,
    -1, 1, -1,      0, 1, -1,
    1, 1, -1,       0, 1, -1,
    
    //  Right face
    1, -1, -1,      1, 0, 0,
    1, -1, -3,      1, 0, 0,
    1, 1, -1,       1, 0, 0,
    1, 1, 1,        1, 0, 0,
    
    //  Left face
    -1, -1, -3,     -1, 0, 0,
    -1, -1, -1,     -1, 0, 0,
    -1, 1, 1,       -1, 0, 0,
    -1, 1, -1,      -1, 0, 0,
    
    //  Top face
    -1, 1, 1,       0, 1, 0,
    1, 1, 1,        0, 1, 0,
    1, 1, -1,       0, 1, 0,
    -1, 1, -1,      0, 1, 0,
    
    //  Bottom face
    -1, -1, -3,     0, -1, 0,
    1, -1, -3,      0, -1, 0,
    1, -1, -1,      0, -1, 0,
    -1, -1, -1,     0, -1, 0,
};

void drawRhombus(float x, float y, float z, float scale_x, float scale_y, float scale_z, float th, float ph, float ze)
{
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rhombusVertexData), rhombusVertexData, GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    // Define normals
    glNormalPointer(GL_FLOAT, 6 * sizeof(float), (void*)12);
    glEnableClientState(GL_NORMAL_ARRAY);

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
    glDrawArrays(GL_QUADS, 0, 24);
    glPopMatrix();

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void drawRhombus_Textured(int textureFile, float x, float y, float z, float scale_x, float scale_y, float scale_z, float th, float ph, float ze)
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
    glBindTexture(GL_TEXTURE_2D,texture[textureFile]);

    glBegin(GL_QUADS);
    
    // Read info from rhombusVertexData to actually draw
    for (int i = 0; i < 6; i++) 
    {
        // Starting address for current face
        int base = 24 * i;
        glColor3f(1,1,1);
        glNormal3f(rhombusVertexData[base + 3], rhombusVertexData[base + 4], rhombusVertexData[base + 5]);
        
        float x1 = rhombusVertexData[base + 0];
        float y1 = rhombusVertexData[base + 1];
        float z1 = rhombusVertexData[base + 2];

        float x2 = rhombusVertexData[base + 6 + 0];
        float y2 = rhombusVertexData[base + 6 + 1];
        float z2 = rhombusVertexData[base + 6 + 2];
        
        float x3 = rhombusVertexData[base + 12 + 0];
        float y3 = rhombusVertexData[base + 12 + 1];
        float z3 = rhombusVertexData[base + 12 + 2];

        float x4 = rhombusVertexData[base + 18 + 0];
        float y4 = rhombusVertexData[base + 18 + 1];
        float z4 = rhombusVertexData[base + 18 + 2];

        glTexCoord2f(0,0); glVertex3f(x1, y1, z1); 
        glTexCoord2f(1,0); glVertex3f(x2, y2, z2); 
        glTexCoord2f(1,1); glVertex3f(x3, y3, z3); 
        glTexCoord2f(0,1); glVertex3f(x4, y4, z4);
    }

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// Vertex method taken from ex13.c
static void Vertex(double th,double ph)
{
   double x = Sin(th)*Cos(ph);
   double y = Cos(th)*Cos(ph);
   double z =         Sin(ph);
   //  For a sphere at the origin, the position
   //  and normal vectors are the same
   glNormal3d(x,y,z);
   glVertex3d(x,y,z);
}

// Ball method taken from ex13.c
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
   //  White ball with yellow specular
   float yellow[]   = {1.0,1.0,0.0,1.0};
   float Emission[] = {0.0f,0.0f,0.01f*emission,1.0f};
   glColor3f(1,1,1);
   glMaterialf(GL_FRONT,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
   glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
   //  Bands of latitude
   for (int ph=-90;ph<90;ph+=inc)
   {
      glBegin(GL_QUAD_STRIP);
      for (int th=0;th<=360;th+=2*inc)
      {
         Vertex(th,ph);
         Vertex(th,ph+inc);
      }
      glEnd();
   }
   //  Undo transofrmations
   glPopMatrix();
}

void GenerateSkybox(float x, float y, float z, float scale_x, float scale_y, float scale_z)
{
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(x,y,z);
    glScalef(scale_x,scale_y,scale_z);

    //  Enable textures
    glEnable(GL_TEXTURE_2D);
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

    //  Front
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,skybox[SKYBOX_FRONT]);
    glBegin(GL_QUADS);
    glNormal3f( 0, 0, -1);
    glTexCoord2f(0,0); glVertex3f(-1,-1, 1);
    glTexCoord2f(0,1); glVertex3f(-1,+1, 1);
    glTexCoord2f(1,1); glVertex3f(+1,+1, 1);
    glTexCoord2f(1,0); glVertex3f(+1,-1, 1);
    glEnd();

    //  Back
    glBindTexture(GL_TEXTURE_2D,skybox[SKYBOX_BACK]);
    glBegin(GL_QUADS);
    glNormal3f( 0,0,1);
    glTexCoord2f(0,0); glVertex3f(+1,-1,-1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,-1);
    glEnd();
    
    //  Left
    glBindTexture(GL_TEXTURE_2D,skybox[SKYBOX_LEFT]);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(1,1); glVertex3f(-1,+1,+1);
    glTexCoord2f(1,0); glVertex3f(-1,-1,+1);
    glEnd();

    //  Right
    glBindTexture(GL_TEXTURE_2D,skybox[SKYBOX_RIGHT]);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glTexCoord2f(0,0); glVertex3f(+1,-1,+1);
    glTexCoord2f(0,1); glVertex3f(+1,+1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glEnd();
    
    //  Top
    glBindTexture(GL_TEXTURE_2D,skybox[SKYBOX_TOP]);
    glBegin(GL_QUADS);
    glNormal3f( 0,-1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,+1,+1);
    glTexCoord2f(0,1); glVertex3f(-1,+1,-1);
    glTexCoord2f(1,1); glVertex3f(+1,+1,-1);
    glTexCoord2f(1,0); glVertex3f(+1,+1,+1);
    glEnd();

    //  Bottom
    glBindTexture(GL_TEXTURE_2D,skybox[SKYBOX_BOTTOM]);
    glBegin(GL_QUADS);
    glNormal3f( 0,1, 0);
    glTexCoord2f(0,0); glVertex3f(-1,-1,-1);
    glTexCoord2f(0,1); glVertex3f(-1,-1,+1);
    glTexCoord2f(1,1); glVertex3f(+1,-1,+1);
    glTexCoord2f(1,0); glVertex3f(+1,-1,-1);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
}

void Project()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (mode == 0)
        glOrtho(-asp*4, asp*3, -3, 3, -10, 10);
    else
        gluPerspective(fov,asp,0.5,30);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw(SDL_Window* window)
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable Depth-Buffer
    glEnable(GL_DEPTH_TEST);

    // Reset transformation matrix
    glLoadIdentity();

    if (mode == 0)
    {
        glRotatef(ph,1,0,0);
        glRotatef(th,0,1,0);
    }
    else if (mode == 1)
    {
        xPos = 1; yPos = 1; zPos = -4;
        gluLookAt(xPos,yPos,-zPos,0,0,0,0,1,0);
    }
    else
    {
        /* Defining the point away from the current location of the player to look at;
        Equations given based off of cylindrical coordinates. */
        xOffset = (Sin(th)*Cos(ph));
        yOffset = Sin(ph);
        zOffset = (Cos(th)*Cos(ph));

        gluLookAt(xPos, yPos, -zPos, xPos + xOffset, yPos + yOffset, -(zPos + zOffset), 0, 1, 0);
    }

    //  Flat or smooth shading
   glShadeModel(smooth ? GL_SMOOTH : GL_FLAT);

   //  Light switch
   if (light)
   {
        //  Translate intensity to color vectors
        float Ambient[]   = {0.01f*ambient ,0.01f*ambient ,0.01f*ambient ,1.0f};
        float Diffuse[]   = {0.01f*diffuse ,0.01f*diffuse ,0.01f*diffuse ,1.0f};
        float Specular[]  = {0.01f*specular,0.01f*specular,0.01f*specular,1.0f};
        //  Light position
        float Position[]  = {distance*(float)Cos(zh),ylight,distance*(float)Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2] , 0.1);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
   else
      glDisable(GL_LIGHTING);

    // Draw axis lines
    glBegin(GL_LINES);  
    // X-axis
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    // Y- axis
    glColor3f(0,1,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
    // Z- axis
    glColor3f(0,0,1);
    glVertex3f(0,0,0);
    glVertex3f(0,0,1);
    glEnd();

    if (objectMode == 0)
    {
        // Draw the stars
        drawStar_Textured(WOOD, 2, 1, -2, 0.3, 0.3, 0.3, 0, -35, z_rot_time);

        glPushMatrix();
        glRotatef(x_rot_time, -1, 0, -1);
        glTranslatef(0.5, 0, -0.5);
        glRotatef(x_rot_time, 1, 0, 0);
        drawStar_Textured(STEEL, 2, 1, -2, 0.3, 0.3, 0.3, 0, 0, 0);
        glPopMatrix();

        glPushMatrix();
        //glColor3f(0, 1, 0.7);
        //drawStar_Colorless(-3, -1, -0.5, 0.3, 0.3, 3, 0, y_rot_time * 1.5, 0);
        glColor3f(0, 1, 0.2);
        drawRhombus_Textured(WATER, -0.25, -1, 0.4, 0.15, 0.3, 0.3, 0, y_rot_time, 0);
        glPopMatrix();

        drawStar_Textured(WOOD, -2, 0, -2, 1, 1, 1, 0, 0, 20);

        // These transformations make the star orbit the big star
        glPushMatrix();
        glTranslatef(-2, 0, -2);
        glRotatef(x_rot_time, 0,1,0);
        glTranslatef(3,0,0);
        drawStar_Textured(STEEL, 0, 0, 0, 0.15, 0.15, 0.15, 0, 0, z_rot_time);
        glColor3f(0,1,0);
        drawWiredCube(0,0,0,0.35,0.35,0.35,x_rot_time,0,z_rot_time);
        glPopMatrix();

        glColor3f(0,0,1);
        drawWiredCube(-0.25,-1,0.4,0.4,0.4,0.5,0,y_rot_time,z_rot_time);

        glColor3f(1,0,0);
        drawWiredCube(2,1,-2,0.5,0.5,0.5,x_rot_time,0,0);
    }
    else if (objectMode == 1)
    {
        drawStar_Textured(WOOD,0,0,0,1,1,1,0,0,0);
    }
    else
    {
        drawWiredCube(0,0,0,0.4,0.4,0.4,0,y_rot_time / 2,0);
        drawRhombus_Textured(WATER,0,0,0,0.15,0.3,0.3,0,0,0);
    }

    if (mode != 0)
        GenerateSkybox(xPos, yPos, -zPos, 10, 10, 10);

    glColor3f(1,1,1);
    glWindowPos2i(5,55);
    Print("Angle theta = %d, Angle phi = %d", th, ph);
    glWindowPos2i(5,30);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
    glWindowPos2i(5,5);
    if (mode == 0)
        Print("Mode: Orthogonal Overview");
    else if (mode == 1)
        Print("Mode: Perspective Overview");
    else
        Print("Mode: First-Person Perspective");
    
    ErrCheck("display");

    glFlush();
    SDL_GL_SwapWindow(window);
}

/* \returns 0 if program is to be closed, 1 otherwise */
int keyDown(SDL_Scancode code)
{
    switch (code)
    {
        case SDL_SCANCODE_ESCAPE:
            return 0;
        
        case SDL_SCANCODE_M:
            mode = (mode + 1) % 3;
            if (mode == 2)
            {
                xPos = 0; yPos = 0; zPos = -1;
            }
            Project();
            break;
        
        case SDL_SCANCODE_W:
            wKeyDown = 1;
            break;
        
        case SDL_SCANCODE_A:
            aKeyDown = 1;
            break;
        
        case SDL_SCANCODE_S:
            sKeyDown = 1;
            break;
        
        case SDL_SCANCODE_D:
            dKeyDown = 1;
            break;
        
        case SDL_SCANCODE_SPACE:
            spaceKeyToggle = (spaceKeyToggle + 1) % 2;
            break;
        
        case SDL_SCANCODE_LEFTBRACKET:
            if (spaceKeyToggle == 1) zh -= 1;
            break;
        
        case SDL_SCANCODE_RIGHTBRACKET:
            if (spaceKeyToggle == 1) zh += 1;
            break;
        
        case SDL_SCANCODE_O:
            objectMode = (objectMode + 1) % 3;
            break;
        
        case SDL_SCANCODE_RIGHT:
            rightKeyDown = 1;
            break;
        
        case SDL_SCANCODE_LEFT:
            leftKeyDown = 1;
            break;
        
        case SDL_SCANCODE_UP:
            upKeyDown = 1;
            break;
        
        case SDL_SCANCODE_DOWN:
            downKeyDown = 1;
            break;
        
        case SDL_SCANCODE_F1:
            if (ambient < 100) ambient += 5;
            break;
        
        case SDL_SCANCODE_F2:
            if (ambient > 0) ambient -= 5;
            break;
        
        case SDL_SCANCODE_F3:
            if (diffuse < 100) diffuse += 5;
            break;
        
        case SDL_SCANCODE_F4:
            if (diffuse > 0) diffuse -= 5;
            break;
        
        case SDL_SCANCODE_F5:
            if (specular < 100) specular += 5;
            break;
        
        case SDL_SCANCODE_F6:
            if (specular > 0) specular -= 5;
            break;
        
        case SDL_SCANCODE_F7:
            if (emission < 100) emission += 5;
            break;
        
        case SDL_SCANCODE_F8:
            if (emission > 0) emission -= 5;
            break;
        
        case SDL_SCANCODE_F9:
            if (shiny < 10) shiny += 1;
            break;
        
        case SDL_SCANCODE_F11:
            if (shiny > 0) shiny -= 1;
            break;
        
        default:
            break;
    }

    return 1;
}

void keyUp(SDL_Scancode code)
{
    switch (code)
    {
        case SDL_SCANCODE_W:
            wKeyDown = 0;
            break;
        
        case SDL_SCANCODE_A:
            aKeyDown = 0;
            break;
        
        case SDL_SCANCODE_S:
            sKeyDown = 0;
            break;
        
        case SDL_SCANCODE_D:
            dKeyDown = 0;
            break;
        
        case SDL_SCANCODE_RIGHT:
            rightKeyDown = 0;
            break;
        
        case SDL_SCANCODE_LEFT:
            leftKeyDown = 0;
            break;
        
        case SDL_SCANCODE_UP:
            upKeyDown = 0;
            break;
        
        case SDL_SCANCODE_DOWN:
            downKeyDown = 0;
            break;
        
        default:
            break;
    }
}

/* This function is used for smooth rotation;
*  Checks for key presses every 10 milliseconds and updates rotation accordingly. */
void timer()
{
    /* Check if keys are pressed down 
    *  If yes, continue rotating. */
    if (!rightKeyDown || !leftKeyDown)
    {
        if (rightKeyDown)
            th += 1;
        else if (leftKeyDown)
            th -= 1;
    }
    if (!upKeyDown || !downKeyDown)
    {
        if (upKeyDown)
            ph += 1;
        else if (downKeyDown)
            ph -= 1;
    }
    
    th %= 360;
    
    if (ph > 90)
        ph = 90;
    if (ph < -90)
        ph = -90;

    // Check if wasd keys are pressed down
    if (!wKeyDown || !sKeyDown)
    {
        if (wKeyDown)
        {
            xPos += xOffset / 35;
            yPos += yOffset / 35;
            zPos += zOffset / 35;
        }
        else if (sKeyDown)
        {
            xPos -= xOffset / 35;
            yPos -= yOffset / 35;
            zPos -= zOffset / 35;
        }
    }
    if (!aKeyDown || !dKeyDown)
    {
        double xOffset_ortho = (Sin(90-th));
        double zOffset_ortho = (Cos(90-th));
        if (aKeyDown)
        {
            xPos -= xOffset_ortho / 35;
            zPos += zOffset_ortho / 35;
        }
        else if (dKeyDown)
        {
            xPos += xOffset_ortho / 35;
            zPos -= zOffset_ortho / 35;
        }
    }

    if (spaceKeyToggle == 0) 
    {
        zh += 1;
        zh %= 360;
    }

    // Update fixed timed rotation values
    x_rot_time += 1;
    y_rot_time += 5;
    z_rot_time += 1;

    x_rot_time %= 360;
    y_rot_time %= 360;
    z_rot_time %= 360;
}

void reshape(SDL_Window* window)
{
    int width, height;

    SDL_GetWindowSize(window, &width, &height);

    asp = (height>0) ? (double)width/height : 1;

    glViewport(0,0, RES*width,RES*height);

    Project();
}

int main(int argc, char* argv[]) 
{
    glutInit(&argc, argv);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("OwenAllison_FinalProject", 
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1300, 900, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_GL_CreateContext(window);                          
    
    #ifdef USEGLEW
    //  Initialize GLEW
    if (glewInit()!=GLEW_OK) fprintf(stderr, "Error initializing GLEW\n");
    #endif

    asp = (float) 1300 / 900;
    
    reshape(window);

    texture[0] = LoadTexBMP("resources/textures/wood.bmp");
    texture[1] = LoadTexBMP("resources/textures/steel.bmp");
    texture[2] = LoadTexBMP("resources/textures/water.bmp");

    skybox[SKYBOX_LEFT] = LoadTexBMP("resources/textures/skybox/left.bmp");
    skybox[SKYBOX_FRONT] = LoadTexBMP("resources/textures/skybox/front.bmp");
    skybox[SKYBOX_RIGHT] = LoadTexBMP("resources/textures/skybox/right.bmp");
    skybox[SKYBOX_BACK] = LoadTexBMP("resources/textures/skybox/back.bmp");
    skybox[SKYBOX_TOP] = LoadTexBMP("resources/textures/skybox/top.bmp");
    skybox[SKYBOX_BOTTOM] = LoadTexBMP("resources/textures/skybox/bottom.bmp");

    ErrCheck("init");

    int run = 1;
    double time = 0;

    while (run)
    {
        double newTime = SDL_GetTicks64()/1000.0;
        double deltaTime = newTime - time;

        if (deltaTime >= 0.01)
        {
            time = newTime;
            timer();
        }

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_WINDOWEVENT:
                    if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        SDL_SetWindowSize(window,event.window.data1,event.window.data2);
                        reshape(window);
                    }
                    break;
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_KEYDOWN:
                    run = keyDown(event.key.keysym.scancode);
                    break;
                case SDL_KEYUP:
                    keyUp(event.key.keysym.scancode);
                    break;
                default:
                    break;
            }
        }

        draw(window);
    }

    SDL_Quit();
    return 0;
}