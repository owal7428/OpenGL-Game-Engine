#include "Engine/Window.hpp"
#include "Engine/Texture.hpp"
#include "Engine/Shader.hpp"
#include "Engine/Utility/util.h"
#include "Engine/Objects/Brushes/Star.hpp"
#include "Engine/Objects/Brushes/Rhombus.hpp"
#include "Engine/Objects/Brushes/Cube.hpp"
#include "Engine/Objects/Brushes/Plane.hpp"
#include "Engine/Objects/Entities/Motor.hpp"
#include "Engine/Objects/Entities/Rotator.hpp"

#define DEFAULT_SHADER "resources/shaders/default"
#define UNLIT_SHADER "resources/shaders/unlit"
#define UNLIT_UNTEXTURED_SHADER "resources/shaders/unlit_untextured"

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
double zFar = 30;
double fov = 90;
int mode = 0;

double xPos = 0;
double yPos = 0;
double zPos = 0;

double xOffset = 0;
double yOffset = 0;
double zOffset = 1;

glm::mat4 projectionMatrix;
glm::mat4 viewMatrix;

int objectMode = 0;

void GenerateSkybox(Plane* sky[], float x, float y, float z)
{
    glm::vec3 lightColor = glm::vec3(1,1,1);

    sky[0] -> Move(glm::vec3(x + zFar,y,z));
    sky[0] -> Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, glm::vec3(0,0,0), lightColor);
    
    sky[1] -> Move(glm::vec3(x - zFar,y,z));
    sky[1] -> Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, glm::vec3(0,0,0), lightColor);

    sky[2] -> Move(glm::vec3(x,y + zFar,z));
    sky[2] -> Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, glm::vec3(0,0,0), lightColor);

    sky[3] -> Move(glm::vec3(x,y - zFar,z));
    sky[3] -> Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, glm::vec3(0,0,0), lightColor);

    sky[4] -> Move(glm::vec3(x,y,z + zFar));
    sky[4] -> Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, glm::vec3(0,0,0), lightColor);

    sky[5] -> Move(glm::vec3(x,y,z - zFar));
    sky[5] -> Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, glm::vec3(0,0,0), lightColor);
}

void Project()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (mode == 0)
    {
        glOrtho(-asp*4, asp*3, -3, 3, -10, 10);
        projectionMatrix = glm::ortho(-asp*4, asp*3, -3.0, 3.0, -10.0, 10.0);
    }
    else
    {
        gluPerspective(fov, asp, 0.5, zFar / Cos(fov));
        projectionMatrix = glm::perspective(glm::radians(fov), asp, 0.5, zFar / Cos(fov));
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void draw(SDL_Window* window, Plane* sky[], Brush* light, std::vector<Brush*>* brushObjects1, std::vector<Brush*>* brushObjects2, std::vector<Brush*>* brushObjects3)
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable Depth-Buffer
    glEnable(GL_DEPTH_TEST);

    // Reset transformation matrix
    glLoadIdentity();

    if (mode == 0 || mode == 1)
    {
        xPos = 1; yPos = 1; zPos = -4;
        gluLookAt(xPos,yPos,-zPos,0,0,0,0,1,0);
        viewMatrix = glm::lookAt(glm::vec3(xPos, yPos, -zPos), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }
    else
    {
        /* Defining the point away from the current location of the player to look at;
        Equations given based off of cylindrical coordinates. */
        xOffset = (Sin(th)*Cos(ph));
        yOffset = Sin(ph);
        zOffset = (Cos(th)*Cos(ph));
        
        gluLookAt(xPos, yPos, -zPos, xPos + xOffset, yPos + yOffset, -(zPos + zOffset), 0, 1, 0);
        viewMatrix = glm::lookAt(glm::vec3(xPos, yPos, -zPos), glm::vec3(xPos + xOffset, yPos + yOffset, -(zPos + zOffset)), glm::vec3(0, 1, 0));
    }

    glm::vec3 lightColor = glm::vec3(0.5, 0.5, 0.5);

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
        int size = brushObjects1->size();

        for (int i = 0; i < size; i++)
            brushObjects1->at(i)->Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, light->getPosition(), lightColor);
    }
    else if (objectMode == 1)
    {
        int size = brushObjects2->size();

        for (int i = 0; i < size; i++)
            brushObjects2->at(i)->Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, light->getPosition(), lightColor);
    }
    else
    {
        int size = brushObjects3->size();

        for (int i = 0; i < size; i++)
            brushObjects3->at(i)->Draw(glm::vec3(xPos, yPos, -zPos), projectionMatrix, viewMatrix, light->getPosition(), lightColor);
    }

    if (mode != 0)
        GenerateSkybox(sky, xPos, yPos, -zPos);

    glColor3f(1,1,1);
    glWindowPos2i(5,30);
    Print("Angle theta = %d, Angle phi = %d", th, ph);
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

    // Compile shaders
    Shader defaultShader(DEFAULT_SHADER);
    Shader unlitShader(UNLIT_SHADER);
    Shader unlitShader_untextured(UNLIT_UNTEXTURED_SHADER);

    asp = (float) 1300 / 900;
    
    reshape(window);
                                                            // Position     // Rotation     // Scale
    Plane SkyboxRight = Plane(&unlitShader, SKYBOX_RIGHT,    zFar, 0, 0,     0, 90, 0,       zFar, zFar, zFar);
    Plane SkyboxLeft = Plane(&unlitShader,  SKYBOX_LEFT,     -zFar, 0, 0,    0, -90., 0,     zFar, zFar, zFar);
    Plane SkyboxTop = Plane(&unlitShader,   SKYBOX_TOP,      0, zFar, 0,     -90., 0, 0,     zFar, zFar, zFar);
    Plane SkyboxBottom = Plane(&unlitShader,SKYBOX_BOTTOM,   0, -zFar, 0,    90, 0, 0,       zFar, zFar, zFar);
    Plane SkyboxFront = Plane(&unlitShader, SKYBOX_FRONT,    0, 0, zFar,     0, 0, 0,        zFar, zFar, zFar);
    Plane SkyboxBack = Plane(&unlitShader,  SKYBOX_BACK,     0, 0, -zFar,    0, 180, 0,      zFar, zFar, zFar);

    Plane* sky[6] = {&SkyboxRight, &SkyboxLeft, &SkyboxTop, &SkyboxBottom, &SkyboxFront, &SkyboxBack};

    // Define objects in the scene
    Star bigStar        =   Star(&defaultShader, WOOD, -2, 0, -2, 0, 0, 20, 1, 1, 1);
    Star bigStarSingle  =   Star(&defaultShader, WOOD, 0, 0, 0, 0, -35, 0, 1, 1, 1);
    Star spinningStar   =   Star(&defaultShader, WOOD, 2, 1, -2, 0, -35, 0, 0.3, 0.3, 0.3);
    Star rotatingStar   =   Star(&defaultShader, STEEL, 1, 0, -2, 0, 0, 0, 0.15, 0.15, 0.15);
    Star otherStar      =   Star(&defaultShader,STEEL, 3, 1, -3, 0, 0, 0, 0.3, 0.3, 0.3);

    Rhombus rhombus         =   Rhombus(&defaultShader, WATER, -0.25, -1, 0.4, 0, 0, 0, 0.15, 0.3, 0.3);
    Rhombus rhombusSingle   =   Rhombus(&defaultShader, WATER, 0, 0, 0, 0.15, 0.3, 0.3, 0.5, 0.5, 0.5);

    Cube spinningStarCube   =   Cube(&unlitShader_untextured, 2, 1, -2, 0, 0, 0, 0.5, 0.5, 0.5);
    Cube rotatingStarCube   =   Cube(&unlitShader_untextured, 1, 0, -2, 0, 0, 0, 0.35, 0.35, 0.35);
    Cube rhombusCube        =   Cube(&unlitShader_untextured, -0.25, -1.0, 0.4, 0.0, 0, 0, 0.4, 0.4, 0.5);
    Cube rhombusCubeSingle  =   Cube(&unlitShader_untextured, 0, 0, 0, 0, 0, 0, 0.4, 0.4, 0.4);

    Cube light = Cube(&unlitShader_untextured, 0, 0, 5, 0, 0, 0, 0.25, 0.25, 0.25);
    light.setColor(1,1,1);

    // Test plane
    Plane testFloor = Plane(&defaultShader, WOOD, 0, -2, 0, -90, 0, 0, 10, 10, 10);

    spinningStarCube.setColor(1, 0, 0);
    rotatingStarCube.setColor(0, 1, 0);
    rhombusCube.setColor(0 ,0, 1);
    rhombusCubeSingle.setColor(0, 0, 1);

    spinningStarCube.EnableRenderWireframe();
    rotatingStarCube.EnableRenderWireframe();
    rhombusCube.EnableRenderWireframe();
    rhombusCubeSingle.EnableRenderWireframe();

    // Define motor entities in the scene
    Motor bigStarSingleMotor = Motor(&bigStarSingle, -(90 - 35), 0, 80);
    Motor spinningStarMotor = Motor(&spinningStar, -(90 - 35), 0, 180);
    Motor rotatingStarMotor1 = Motor(&rotatingStar, -90, 0, 80);
    Motor rotatingStarMotor2 = Motor(&rotatingStar, 0, 90, 90);
    Motor otherStarMotor1 = Motor(&otherStar, 0, 0, 100);
    Motor otherStarMotor2 = Motor(&otherStar, 0, -90, 75);

    Motor rhombusMotor = Motor(&rhombus, 0, 90, 720);

    Motor spinningStarCubeMotor = Motor(&spinningStarCube, 0, 0, 100);

    Motor rotatingStarCubeMotor1 = Motor(&rotatingStarCube, -90, 0, 100);
    Motor rotatingStarCubeMotor2 = Motor(&rotatingStarCube, 0, 0, 100);

    Motor rhombusCubeMotor1 = Motor(&rhombusCube, -90, 0, 150);
    Motor rhombusCubeMotor2 = Motor(&rhombusCube, 0, 90, 150);

    Motor rhombusCubeSingleMotor = Motor(&rhombusCubeSingle, 0, 90, 180);

    Motor lightMotor = Motor(&light, 0, 90, 135);

    Rotator rotatingStarRotator = Rotator(&rotatingStar, -2, 0, -2, 0, 90, 90);
    Rotator rotatingStarCubeRotator = Rotator(&rotatingStarCube, -2, 0, -2, 0, 90, 90);
    Rotator otherStarRotator = Rotator(&otherStar, 2, 1, -2, -1, 0, -1, 100);

    Rotator lightRotator = Rotator(&light, 0, 0, 0, 0, 90, 75);

    std::vector<Brush*> brushObjects1;

    brushObjects1.push_back(&bigStar);
    brushObjects1.push_back(&spinningStar);
    brushObjects1.push_back(&rotatingStar);
    brushObjects1.push_back(&otherStar);

    brushObjects1.push_back(&rhombus);

    brushObjects1.push_back(&spinningStarCube);
    brushObjects1.push_back(&rotatingStarCube);
    brushObjects1.push_back(&rhombusCube);

    brushObjects1.push_back(&light);

    std::vector<Brush*> brushObjects2;
    
    brushObjects2.push_back(&rhombusSingle);
    brushObjects2.push_back(&rhombusCubeSingle);
    brushObjects2.push_back(&testFloor);
    brushObjects2.push_back(&light);

    std::vector<Brush*> brushObjects3;
    
    brushObjects3.push_back(&bigStarSingle);
    
    brushObjects3.push_back(&light);

    std::vector<Motor*> motorObjects;

    motorObjects.push_back(&spinningStarMotor);
    motorObjects.push_back(&rotatingStarMotor1);
    motorObjects.push_back(&rotatingStarMotor2);
    motorObjects.push_back(&otherStarMotor1);
    motorObjects.push_back(&otherStarMotor2);

    motorObjects.push_back(&rhombusMotor);

    motorObjects.push_back(&rotatingStarCubeMotor1);
    motorObjects.push_back(&rotatingStarCubeMotor2);

    motorObjects.push_back(&spinningStarCubeMotor);

    motorObjects.push_back(&rhombusCubeMotor1);
    motorObjects.push_back(&rhombusCubeMotor2);

    motorObjects.push_back(&rhombusCubeSingleMotor);
    
    motorObjects.push_back(&bigStarSingleMotor);

    motorObjects.push_back(&lightMotor);

    std::vector<Rotator*> rotatorObjects;

    rotatorObjects.push_back(&rotatingStarRotator);
    rotatorObjects.push_back(&rotatingStarCubeRotator);
    rotatorObjects.push_back(&otherStarRotator);

    rotatorObjects.push_back(&lightRotator);

    ErrCheck("init");

    int run = 1;
    double time = 0;

    while (run)
    {
        double newTime = SDL_GetTicks64()/1000.0;
        double deltaTime = newTime - time;

        // Do this every 0.01 seconds (10 ms)
        if (deltaTime >= 0.01)
        {
            time = newTime;
            timer();
            
            // Reset rotations to avoid accelerating to infinity
            int brushListSize1 = brushObjects1.size();
            
            for (int i = 0; i < brushListSize1; i++)
                brushObjects1.at(i)->ResetRotations();

            int brushListSize2 = brushObjects2.size();
            
            for (int i = 0; i < brushListSize2; i++)
                brushObjects2.at(i)->ResetRotations();
            
            int brushListSize3 = brushObjects3.size();
            
            for (int i = 0; i < brushListSize3; i++)
                brushObjects3.at(i)->ResetRotations();
            
            // Call actors
            int motorListSize = motorObjects.size();

            for (int i = 0; i < motorListSize; i++)
                motorObjects.at(i)->Spin(deltaTime);

            int rotatorListSize = rotatorObjects.size();

            for (int i = 0; i < rotatorListSize; i++)
                rotatorObjects.at(i)->Rotate(deltaTime);
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

        draw(window, sky, &light, &brushObjects1, &brushObjects2, &brushObjects3);
    }

    SDL_Quit();
    return 0;
}
