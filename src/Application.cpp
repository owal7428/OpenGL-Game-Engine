#include "Engine/Window.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Utility/util.h"
#include "Engine/Objects/Brushes/Star.hpp"
#include "Engine/Objects/Brushes/Rhombus.hpp"
#include "Engine/Objects/Brushes/Cube.hpp"
#include "Engine/Objects/Brushes/Plane.hpp"

#define WOOD "resources/textures/wood.bmp"
#define STEEL "resources/textures/steel.bmp"
#define WATER "resources/textures/water.bmp"

#define SKYBOX_FRONT "resources/textures/skybox/front.bmp"
#define SKYBOX_BACK "resources/textures/skybox/back.bmp"
#define SKYBOX_LEFT "resources/textures/skybox/left.bmp"
#define SKYBOX_RIGHT "resources/textures/skybox/right.bmp"
#define SKYBOX_TOP "resources/textures/skybox/top.bmp"
#define SKYBOX_BOTTOM "resources/textures/skybox/bottom.bmp"

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
int zFar = 30;
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

void drawStar(float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z)
{
    Star star = Star(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);
    star.Draw(emission, shiny);
}

void drawStar_Textured(const char* textureFile, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z)
{
    Star star = Star(textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);
    star.Draw(emission, shiny);
}

void drawRhombus(float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z)
{
    Rhombus rhombus = Rhombus(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);
    rhombus.Draw(emission, shiny);
}

void drawRhombus_Textured(const char* textureFile, float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z)
{
    Rhombus rhombus = Rhombus(textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);
    rhombus.Draw(emission,shiny);
}

void drawWiredCube(float x, float y, float z, float rot_x, float rot_y, float rot_z, float scale_x, float scale_y, float scale_z)
{
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDisable(GL_LIGHTING);

    Cube newCube = Cube(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z);
    newCube.Draw(emission,shiny);

    glEnable(GL_LIGHTING);
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
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

void GenerateSkybox(Plane sky[], float x, float y, float z)
{
    glDisable(GL_LIGHTING);

    sky[0].Move(glm::vec3(x + zFar,y,z));
    sky[0].Draw(emission, shiny);
    
    sky[1].Move(glm::vec3(x - zFar,y,z));
    sky[1].Draw(emission, shiny);

    sky[2].Move(glm::vec3(x,y + zFar,z));
    sky[2].Draw(emission, shiny);

    sky[3].Move(glm::vec3(x,y - zFar,z));
    sky[3].Draw(emission, shiny);

    sky[4].Move(glm::vec3(x,y,z + zFar));
    sky[4].Draw(emission, shiny);

    sky[5].Move(glm::vec3(x,y,z - zFar));
    sky[5].Draw(emission, shiny);

    glEnable(GL_LIGHTING);
}

void Project()
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (mode == 0)
        glOrtho(-asp*4, asp*3, -3, 3, -10, 10);
    else
        gluPerspective(fov,asp,0.5, zFar / Cos(fov));


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw(SDL_Window* window, Plane sky[])
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
        drawStar_Textured(WOOD, 2, 1, -2, 0, -35, z_rot_time, 0.3, 0.3, 0.3);

        glPushMatrix();
        glRotatef(x_rot_time, -1, 0, -1);
        glTranslatef(0.5, 0, -0.5);
        glRotatef(x_rot_time, 1, 0, 0);
        drawStar_Textured(STEEL, 2, 1, -2, 0, 0, 0, 0.3, 0.3, 0.3);
        glPopMatrix();

        glPushMatrix();
        //glColor3f(0, 1, 0.7);
        //drawStar_Colorless(-3, -1, -0.5, 0.3, 0.3, 3, 0, y_rot_time * 1.5, 0);
        glColor3f(0, 1, 0.2);
        drawRhombus_Textured(WATER, -0.25, -1, 0.4, 0, y_rot_time, 0, 0.15, 0.3, 0.3);
        glPopMatrix();

        drawStar_Textured(WOOD, -2, 0, -2, 0, 0, 20, 1, 1, 1);

        // These transformations make the star orbit the big star
        glPushMatrix();
        glTranslatef(-2, 0, -2);
        glRotatef(x_rot_time, 0,1,0);
        glTranslatef(3,0,0);

        drawStar_Textured(STEEL, 0, 0, 0, 0, 0, z_rot_time, 0.15, 0.15, 0.15);

        glColor3f(0,1,0);
        drawWiredCube(0, 0, 0, x_rot_time, 0, z_rot_time, 0.35, 0.35, 0.35);
        glPopMatrix();

        glColor3f(0,0,1);
        drawWiredCube(-0.25, -1.0, 0.4, 0.0, y_rot_time, z_rot_time, 0.4, 0.4, 0.5);

        glColor3f(1,0,0);
        drawWiredCube(2, 1, -2, x_rot_time, 0, 0, 0.5, 0.5, 0.5);
    }
    else if (objectMode == 1)
    {
        drawStar_Textured(WOOD, 0, 0, 0, 0, -35, z_rot_time, 1, 1, 1);
    }
    else
    {
        drawWiredCube(0, 0, 0, 0, y_rot_time / 2, 0, 0.4, 0.4, 0.4);
        drawRhombus_Textured(WATER, 0, 0, 0, 0.15, 0.3, 0.3, 0.5, 0.5, 0.5);
    }

    if (mode != 0)
        GenerateSkybox(sky, xPos, yPos, -zPos);

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

void keyDown(SDL_Scancode code)
{
    switch (code)
    { 
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
                                                // Position     // Rotation     // Scale
    Plane SkyboxRight = Plane(SKYBOX_RIGHT,     zFar, 0, 0,     0, 90, 0,       zFar, zFar, zFar);
    Plane SkyboxLeft = Plane(SKYBOX_LEFT,       -zFar, 0, 0,    0, -90., 0,     zFar, zFar, zFar);
    Plane SkyboxTop = Plane(SKYBOX_TOP,         0, zFar, 0,     -90., 0, 0,     zFar, zFar, zFar);
    Plane SkyboxBottom = Plane(SKYBOX_BOTTOM,   0, -zFar, 0,    90, 0, 0,       zFar, zFar, zFar);
    Plane SkyboxFront = Plane(SKYBOX_FRONT,     0, 0, zFar,     0, 0, 0,        zFar, zFar, zFar);
    Plane SkyboxBack = Plane(SKYBOX_BACK,       0, 0, -zFar,    0, 180, 0,      zFar, zFar, zFar);

    Plane sky[6] = {SkyboxRight, SkyboxLeft, SkyboxTop, SkyboxBottom, SkyboxFront, SkyboxBack};

    // Define objects in the scene
    Star bigStar        =   Star(WOOD, -2, 0, -2, 0, 0, 20, 1, 1, 1);
    Star rotatingStar   =   Star(STEEL, 0, 0, 0, 0, 0, z_rot_time, 0.15, 0.15, 0.15);
    Star spinningStar   =   Star(WOOD, 2, 1, -2, 0, -35, z_rot_time, 0.3, 0.3, 0.3);
    Star otherStar      =   Star(STEEL, 2, 1, -2, 0, 0, 0, 0.3, 0.3, 0.3);

    Rhombus rhombus     =   Rhombus(WATER, -0.25, -1, 0.4, 0, y_rot_time, 0, 0.15, 0.3, 0.3);

    Cube rotatingStarCube   =   Cube(0, 0, 0, x_rot_time, 0, z_rot_time, 0.35, 0.35, 0.35);
    Cube spinningStarCube   =   Cube(2, 1, -2, x_rot_time, 0, 0, 0.5, 0.5, 0.5);
    Cube rhombusCube        =   Cube(-0.25, -1.0, 0.4, 0.0, y_rot_time, z_rot_time, 0.4, 0.4, 0.5);

    ErrCheck("init");

    int run = 1;
    double time = 0;

    while (run)
    {
        double newTime = SDL_GetTicks64()/1000.0;
        double deltaTime = newTime - time;

        // Do this every 0.01 seconds
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
                        int width = event.window.data1;
                        int height = event.window.data2;
                        SDL_SetWindowSize(window, width, height);
                        reshape(window);
                    }
                    break;
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_KEYDOWN:
                    // Exit event loop if escape key is pressed
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        run = 0;
                    else
                        keyDown(event.key.keysym.scancode);
                    break;
                case SDL_KEYUP:
                    keyUp(event.key.keysym.scancode);
                    break;
                default:
                    break;
            }
        }

        draw(window, sky);
    }

    SDL_Quit();
    return 0;
}
