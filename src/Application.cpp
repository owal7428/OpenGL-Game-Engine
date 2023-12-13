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
#include "Engine/Objects/Entities/Camera.hpp"
#include "Engine/Objects/Entities/Lights/PointLight.hpp"
#include "Engine/Objects/Entities/Lights/DirectionalLight.hpp"
#include "Engine/Objects/Physics/PlaneCollider.hpp"
#include "Engine/Objects/Physics/BoxCollider.hpp"

#define DEFAULT_SHADER "resources/shaders/default"
#define UNLIT_SHADER "resources/shaders/unlit"
#define UNLIT_UNTEXTURED_SHADER "resources/shaders/unlit_untextured"

#define WOOD "resources/textures/wood.bmp"
#define DARK_WOOD "resources/textures/dark_wood.bmp"
#define STEEL "resources/textures/steel.bmp"
#define TREAD_STEEL "resources/textures/tread_steel.bmp"
#define BRICK "resources/textures/brick.bmp"
#define BRICK2 "resources/textures/brick_2.bmp"
#define ROCKS "resources/textures/rocks.bmp"
#define DARK_SKY "resources/textures/dark_sky.bmp"
#define WINDOW "resources/textures/window.bmp"
#define LAVA "resources/textures/lava.bmp"

#define SKYBOX_FRONT "resources/textures/skybox/front.bmp"
#define SKYBOX_BACK "resources/textures/skybox/back.bmp"
#define SKYBOX_LEFT "resources/textures/skybox/left.bmp"
#define SKYBOX_RIGHT "resources/textures/skybox/right.bmp"
#define SKYBOX_TOP "resources/textures/skybox/top.bmp"
#define SKYBOX_BOTTOM "resources/textures/skybox/bottom.bmp"

double asp = 1;
double zFar = 500;
double fov = 90;

void GenerateSkybox(Plane* sky[], glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    sky[0] -> Move(cameraPosition - glm::vec3(zFar, 0, 0));
    sky[0] -> Draw(cameraPosition, projectionMatrix, viewMatrix);
    
    sky[1] -> Move(cameraPosition + glm::vec3(zFar, 0, 0));
    sky[1] -> Draw(cameraPosition, projectionMatrix, viewMatrix);

    sky[2] -> Move(cameraPosition + glm::vec3(0, zFar, 0));
    sky[2] -> Draw(cameraPosition, projectionMatrix, viewMatrix);

    sky[3] -> Move(cameraPosition - glm::vec3(0, zFar, 0));
    sky[3] -> Draw(cameraPosition, projectionMatrix, viewMatrix);

    sky[4] -> Move(cameraPosition + glm::vec3(0, 0, zFar));
    sky[4] -> Draw(cameraPosition, projectionMatrix, viewMatrix);

    sky[5] -> Move(cameraPosition - glm::vec3(0, 0, zFar));
    sky[5] -> Draw(cameraPosition, projectionMatrix, viewMatrix);
}

void Project(Camera* camera)
{

    camera -> UpdateProjection(fov, asp, 0.25, zFar / Cos(fov));

    #ifndef __APPLE__

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, asp, 0.25, zFar / Cos(fov));

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    #endif


}

void draw(SDL_Window* window, Camera* camera, Plane* sky[], DirectionalLight* sun, std::vector<PointLight*> pointLights, std::vector<Brush*>* brushObjects)
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable Depth-Buffer
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE); 

    glm::vec3 position = camera -> getPosition();

    #ifndef __APPLE__

    glm::vec3 lookingAt = camera -> getLookingAt();
    
    glLoadIdentity();

    gluLookAt(position.x, position.y, position.z, position.x + lookingAt.x, position.y + lookingAt.y, position.z + lookingAt.z, 0, 1, 0);

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

    #endif

    int size = brushObjects -> size();

    for (int i = 0; i < size; i++)
        brushObjects->at(i)->Draw(position, camera -> getProjectionMatrix(), camera -> getViewMatrix(), sun, pointLights);

    GenerateSkybox(sky, position, camera -> getProjectionMatrix(), camera -> getViewMatrix());
   
   ErrCheck("display");
   
   glFlush();
   SDL_GL_SwapWindow(window);
}

void reshape(SDL_Window* window, Camera* camera)
{
    int width, height;

    SDL_GetWindowSize(window, &width, &height);

    asp = (height>0) ? (double)width/height : 1;

    glViewport(0,0, RES*width,RES*height);

    Project(camera);
}

/* This function is used for smooth rotation;
*  Checks for key presses every 10 milliseconds and updates rotation accordingly. */
void Update()
{
    // Do nothing for now
}

int main(int argc, char* argv[]) 
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("OwenAllison_FinalProject", 
                                          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1300, 900, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    #if defined(__APPLE__)
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        printf("Set gl version to 330 core.\n");
    #endif

    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    bool catchMouse = true;

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

    Camera camera = Camera(0, 5, 0, fov, asp, 0.25, zFar / Cos(fov), 12, 10);
    
    reshape(window, &camera);

    ErrCheck("init");
                                                            // Position     // Rotation     // Scale
    Plane SkyboxRight = Plane(&unlitShader, SKYBOX_RIGHT,   -zFar, 0, 0,    0, 90, 0,       zFar*2, zFar*2, zFar*2);
    Plane SkyboxLeft = Plane(&unlitShader,  SKYBOX_LEFT,    zFar, 0, 0,     0, -90, 0,      zFar*2, zFar*2, zFar*2);
    Plane SkyboxTop = Plane(&unlitShader,   SKYBOX_TOP,     0, zFar, 0,     -90, 180, 0,    zFar*2, zFar*2, zFar*2);
    Plane SkyboxBottom = Plane(&unlitShader,SKYBOX_BOTTOM,  0, -zFar, 0,    90, 180, 0,     zFar*2, zFar*2, zFar*2);
    Plane SkyboxFront = Plane(&unlitShader, SKYBOX_FRONT,   0, 0, zFar,     0, -180, 0,     zFar*2, zFar*2, zFar*2);
    Plane SkyboxBack = Plane(&unlitShader,  SKYBOX_BACK,    0, 0, -zFar,    0, 0, 0,        zFar*2, zFar*2, zFar*2);

    Plane* sky[6] = {&SkyboxRight, &SkyboxLeft, &SkyboxTop, &SkyboxBottom, &SkyboxFront, &SkyboxBack};

    // Define objects in the scene

    //DirectionalLight sun = DirectionalLight(0, -0.5, -1, 0.86, 0.63, 0.34, 0.33, 0.70, 0.86, 0.75, 0.75, 0.75);
    DirectionalLight sun = DirectionalLight(1, -1, -0.1, 1  * 0.2, 0.97  * 0.2, 0.81 * 0.2, 1, 0.97, 0.81, 0.75, 0.75, 0.75);

    std::vector<PointLight*> lights;

    PointLight rotatingLight = PointLight(0, 0, 10, 1, 1, 1, 1.0, 1.0, 1.0, 0.75, 0.07, 0.017);
    lights.push_back(&rotatingLight);

    PointLight lavaPointLight = PointLight(-11, 1, 29, 1, 0.5, 0.2, 1.0, 1.0, 1.0, 0.75, 0.07, 0.017);
    lights.push_back(&lavaPointLight);

    PointLight windowLight = PointLight(11, 3, 28, 1, 0.8, 0.65, 1.0, 1.0, 1.0, 0.75, 0.07, 0.017);
    lights.push_back(&windowLight);

    // Define motor entities in the scene
    

    std::vector<Brush*> brushObjects;

    Cube floor = Cube(&defaultShader, BRICK2, 0, -3, 9.5, 0, 0, 0, 33, 4, 25);
    floor.setColor(1, 0.8, 0.7);
    floor.setTextureScale(5);
    brushObjects.push_back(&floor);

    Cube platform = Cube(&defaultShader, BRICK2, 0, 0.375, 0, 0, 0, 0, 33, 2.75, 6);
    platform.setTextureScaleX(4);
    brushObjects.push_back(&platform);

    Cube leftWall = Cube(&defaultShader, BRICK, 17.5, 1.5, 9.5, 0, 0, 0, 2, 9, 25);
    leftWall.setColor(1, 0.8, 0.5);
    leftWall.setTextureScaleY(1);
    leftWall.setTextureScaleX(5);
    brushObjects.push_back(&leftWall);

    Cube leftWall2 = Cube(&defaultShader, BRICK, 17.5, 1, 34.5, 0, 0, 0, 2, 12, 25);
    leftWall2.setColor(1, 0.8, 0.5);
    leftWall2.setTextureScaleY(1.25);
    leftWall2.setTextureScaleX(5);
    brushObjects.push_back(&leftWall2);

    Cube middleLeftWall = Cube(&defaultShader, BRICK, 5.5, 1, 34.5, 0, 0, 0, 1, 12, 25);
    middleLeftWall.setColor(1, 0.8, 0.5);
    middleLeftWall.setTextureScaleY(1.25);
    middleLeftWall.setTextureScaleX(5);
    brushObjects.push_back(&middleLeftWall);

    Cube middleRightWall = Cube(&defaultShader, BRICK, -5.5, 1, 34.5, 0, 0, 0, 1, 12, 25);
    middleRightWall.setColor(1, 0.8, 0.5);
    middleRightWall.setTextureScaleY(1.25);
    middleRightWall.setTextureScaleX(5);
    brushObjects.push_back(&middleRightWall);

    Cube rightWall = Cube(&defaultShader, BRICK, -17.5, 1.5, 9.5, 0, 0, 0, 2, 9, 25);
    rightWall.setColor(1, 0.8, 0.5);
    rightWall.setTextureScaleY(1);
    rightWall.setTextureScaleX(5);
    brushObjects.push_back(&rightWall);

    Cube rightWall2 = Cube(&defaultShader, ROCKS, -17.5, 1, 34.5, 0, 0, 0, 2, 12, 25);
    rightWall2.setTextureScaleY(3);
    rightWall2.setTextureScaleX(5);
    brushObjects.push_back(&rightWall2);

    Cube backWall = Cube(&defaultShader, BRICK, 0, 3.75, -4, 0, 0, 0, 37, 4.5, 2);
    backWall.setColor(1, 0.8, 0.5);
    backWall.setTextureScaleY(0.5);
    backWall.setTextureScaleX(4);
    brushObjects.push_back(&backWall);

    Cube pillar1 = Cube(&defaultShader, TREAD_STEEL, -5.5, 3, 21, 0, 0, 0, 2, 8, 2);
    pillar1.setTextureScaleY(1.5);
    brushObjects.push_back(&pillar1);

    Cube pillar2 = Cube(&defaultShader, TREAD_STEEL, 5.5, 3, 21, 0, 0, 0, 2, 8, 2);
    pillar2.setTextureScaleY(1.5);
    brushObjects.push_back(&pillar2);

    Cube pillar3 = Cube(&defaultShader, TREAD_STEEL, 16, 3, 21, 0, 0, 0, 1, 8, 2);
    pillar3.setTextureScaleY(1.5);
    brushObjects.push_back(&pillar3);

    Cube pillar4 = Cube(&defaultShader, TREAD_STEEL, -16, 3, 21, 0, 0, 0, 1, 8, 2);
    pillar4.setTextureScaleY(1.5);
    brushObjects.push_back(&pillar4);

    Cube bigPillar = Cube(&defaultShader, TREAD_STEEL, 0, 8, 21, 0, 0, 0, 22, 2, 2);
    bigPillar.setTextureScaleY(1.5);
    bigPillar.setTextureScaleX(3);
    brushObjects.push_back(&bigPillar);

    Rhombus leftRhombus = Rhombus(&defaultShader, TREAD_STEEL, 13.25, 6, 21, 0, -90, 0, 2, 4.5, 2);
    leftRhombus.setTextureScaleY(1.5);
    brushObjects.push_back(&leftRhombus);

    leftRhombus.SetRotation(glm::angleAxis(glm::radians(90.0f), glm::vec3(0,0,1)) * leftRhombus.getRotation());
    leftRhombus.SetRotation(glm::angleAxis(glm::radians(180.0f), glm::vec3(0,1,0)) * leftRhombus.getRotation());

    Rhombus rightRhombus = Rhombus(&defaultShader, TREAD_STEEL, -13.25, 6, 21, 0, 90, 0, 2, 4.5, 2);
    rightRhombus.setTextureScaleY(1.5);
    brushObjects.push_back(&rightRhombus);

    rightRhombus.SetRotation(glm::angleAxis(glm::radians(-90.0f), glm::vec3(0,0,1)) * rightRhombus.getRotation());
    rightRhombus.SetRotation(glm::angleAxis(glm::radians(-180.0f), glm::vec3(0,1,0)) * rightRhombus.getRotation());

    Cube leftLane = Cube(&defaultShader, BRICK2, 11, -2 , 34.5, 0, 0, 0, 11, 2, 25);
    leftLane.setColor(1, 0.8, 0.7);
    leftLane.setTextureScaleY(5);
    leftLane.setTextureScaleX(2);
    brushObjects.push_back(&leftLane);

    Cube rightLane = Cube(&defaultShader, BRICK2, -11, -3 , 41, 0, 0, 0, 11, 4, 12);
    rightLane.setColor(1, 0.8, 0.7);
    rightLane.setTextureScaleY(5);
    rightLane.setTextureScaleX(2);
    brushObjects.push_back(&rightLane);

    Cube middleLane = Cube(&defaultShader, BRICK2, 0, -2 , 34.5, 0, 0, 0, 11, 2, 25);
    middleLane.setColor(1, 0.8, 0.7);
    middleLane.setTextureScaleY(5);
    middleLane.setTextureScaleX(2);
    brushObjects.push_back(&middleLane);

    Cube rightLane2 = Cube(&defaultShader, ROCKS, -11, -3, 24, 0, 0, 0, 6, 4, 4);
    rightLane2.setColor(1, 0.8, 0.7);
    rightLane2.setTextureScaleY(5);
    rightLane2.setTextureScaleX(2);
    brushObjects.push_back(&rightLane2);

    Cube lavalFloor = Cube(&defaultShader, ROCKS, -11, -5, 29, 0, 0, 0, 11, 1, 14);
    lavalFloor.setTextureScaleY(5);
    lavalFloor.setTextureScaleX(2);
    brushObjects.push_back(&lavalFloor);

    Cube lavaPlane = Cube(&unlitShader, LAVA, -11, -3, 29, 0, 0, 0, 11, 1, 14);
    lavaPlane.setTextureScale(5);
    brushObjects.push_back(&lavaPlane);

    Cube windowPlane = Cube(&unlitShader, WINDOW, 11, 3, 30, 0, 0, 0, 2, 5, 2);
    brushObjects.push_back(&windowPlane);

    Cube leftEndWall1 = Cube(&defaultShader, BRICK2, 11.25, -0.25, 30, 0, 0, 0, 10.5, 1.5, 2);
    leftEndWall1.setTextureScaleX(4);
    brushObjects.push_back(&leftEndWall1);

    Cube leftEndWall2 = Cube(&defaultShader, BRICK2, 14.25, 3, 30, 0, 0, 0, 4.5, 5, 2);
    brushObjects.push_back(&leftEndWall2);

    Cube leftEndWall3 = Cube(&defaultShader, BRICK2, 11.25, 6.25, 30, 0, 0, 0, 10.5, 1.5, 2);
    leftEndWall3.setTextureScaleX(4);
    brushObjects.push_back(&leftEndWall3);

    Cube leftEndWall4 = Cube(&defaultShader, BRICK2, 7.75, 3, 30, 0, 0, 0, 4.5, 5, 2);
    brushObjects.push_back(&leftEndWall4);
    
    Cube rightLaneEnd = Cube(&defaultShader, BRICK2, -11.25, 3, 46, 0, 0, 0, 10.5, 8, 2);
    brushObjects.push_back(&rightLaneEnd);

    Cube middleLaneEnd = Cube(&defaultShader, BRICK2, 0, 3, 35, 0, 0, 0, 10.5, 8, 2);
    brushObjects.push_back(&middleLaneEnd);

    Cube rotatingCube = Cube(&unlitShader_untextured, 0, 3, 6, 0, 0, 0, 1, 1, 1);
    rotatingCube.setColor(1,1,1);
    rotatingCube.AddChild(&rotatingLight);
    brushObjects.push_back(&rotatingCube);

    std::vector<Collider*> colliders;

    BoxCollider floorCollider = BoxCollider(&camera, floor.getPosition(), floor.getRotation(), floor.getScale());
    colliders.push_back(&floorCollider);

    BoxCollider platformCollider = BoxCollider(&camera, platform.getPosition(), platform.getRotation(), platform.getScale());
    colliders.push_back(&platformCollider);

    BoxCollider leftWallCollider = BoxCollider(&camera, leftWall.getPosition(), leftWall.getRotation(), leftWall.getScale());
    colliders.push_back(&leftWallCollider);

    BoxCollider leftWallCollider2 = BoxCollider(&camera, leftWall2.getPosition(), leftWall2.getRotation(), leftWall2.getScale());
    colliders.push_back(&leftWallCollider2);

    BoxCollider middleLeftWallCollider = BoxCollider(&camera, middleLeftWall.getPosition(), middleLeftWall.getRotation(), middleLeftWall.getScale());
    colliders.push_back(&middleLeftWallCollider);
    
    BoxCollider middleRightWallCollider = BoxCollider(&camera, middleRightWall.getPosition(), middleRightWall.getRotation(), middleRightWall.getScale());
    colliders.push_back(&middleRightWallCollider);

    BoxCollider rightWallCollider = BoxCollider(&camera, rightWall.getPosition(), rightWall.getRotation(), rightWall.getScale());
    colliders.push_back(&rightWallCollider);

    BoxCollider rightWall2Collider = BoxCollider(&camera, rightWall2.getPosition(), rightWall2.getRotation(), rightWall2.getScale());
    colliders.push_back(&rightWall2Collider);

    BoxCollider backWallCollider = BoxCollider(&camera, backWall.getPosition(), backWall.getRotation(), backWall.getScale());
    colliders.push_back(&backWallCollider);

    BoxCollider pillar1Collider = BoxCollider(&camera, pillar1.getPosition(), pillar1.getRotation(), pillar1.getScale());
    colliders.push_back(&pillar1Collider);

    BoxCollider pillar2Collider = BoxCollider(&camera, pillar2.getPosition(), pillar2.getRotation(), pillar2.getScale());
    colliders.push_back(&pillar2Collider);

    BoxCollider pillar3Collider = BoxCollider(&camera, pillar3.getPosition(), pillar3.getRotation(), pillar3.getScale());
    colliders.push_back(&pillar3Collider);

    BoxCollider pillar4Collider = BoxCollider(&camera, pillar4.getPosition(), pillar4.getRotation(), pillar4.getScale());
    colliders.push_back(&pillar4Collider);

    BoxCollider leftLaneCollider = BoxCollider(&camera, leftLane.getPosition(), leftLane.getRotation(), leftLane.getScale());
    colliders.push_back(&leftLaneCollider);

    BoxCollider rightLaneCollider = BoxCollider(&camera, rightLane.getPosition(), rightLane.getRotation(), rightLane.getScale());
    colliders.push_back(&rightLaneCollider);
    
    BoxCollider middleLaneCollider = BoxCollider(&camera, middleLane.getPosition(), middleLane.getRotation(), middleLane.getScale());
    colliders.push_back(&middleLaneCollider);
    
    BoxCollider rightLane2Collider = BoxCollider(&camera, rightLane2.getPosition(), rightLane2.getRotation(), rightLane2.getScale());
    colliders.push_back(&rightLane2Collider);

    BoxCollider lavalFloorCollider = BoxCollider(&camera, lavalFloor.getPosition(), lavalFloor.getRotation(), lavalFloor.getScale());
    colliders.push_back(&lavalFloorCollider);

    BoxCollider leftLaneEndCollider = BoxCollider(&camera, glm::vec3(11.25, 3, 30), glm::vec3(0, 0, 0), glm::vec3(10.5, 8, 2));
    colliders.push_back(&leftLaneEndCollider);
    
    BoxCollider rightLaneEndCollider = BoxCollider(&camera, rightLaneEnd.getPosition(), rightLaneEnd.getRotation(), rightLaneEnd.getScale());
    colliders.push_back(&rightLaneEndCollider);
    
    BoxCollider middleLaneEndCollider = BoxCollider(&camera, middleLaneEnd.getPosition(), middleLaneEnd.getRotation(), middleLaneEnd.getScale());
    colliders.push_back(&middleLaneEndCollider);

    std::vector<Motor*> motorObjects;

    Motor boxMotor = Motor(&rotatingCube, 0, 90, 150);
    motorObjects.push_back(&boxMotor);

    std::vector<Rotator*> rotatorObjects;

    Rotator boxRotator = Rotator(&rotatingCube, 0, 3, 11, 0, 90, 150);
    rotatorObjects.push_back(&boxRotator);

    int run = 1;
    double time = SDL_GetTicks64()/1000.0;

    while (run)
    {
        double newTime = SDL_GetTicks64()/1000.0;
        double deltaTime = newTime - time;

        // Do this every 0.01 seconds (10 ms)
        if (deltaTime >= 0.01)
        {
            time = newTime;
            Update();

            camera.Update(deltaTime);
            
            // Reset rotations to avoid accelerating to infinity
            rotatingCube.ResetRotations();
            
            // Call actors
            int motorListSize = motorObjects.size();

            for (int i = 0; i < motorListSize; i++)
                motorObjects.at(i)->Spin(deltaTime);

            int rotatorListSize = rotatorObjects.size();

            for (int i = 0; i < rotatorListSize; i++)
                rotatorObjects.at(i)->Rotate(deltaTime);
        }

        glm::vec3 pos = camera.getPosition();

        int colliderSize = colliders.size();
        for (int i = 0; i < colliderSize; i++)
            colliders.at(i)->CollisionTest(pos);

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
                        reshape(window, &camera);
                    }
                    break;
                case SDL_QUIT:
                    run = 0;
                    break;
                case SDL_KEYDOWN:
                    // Exit event loop if escape key is pressed
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        run = 0;
                    else if (event.key.keysym.scancode == SDL_SCANCODE_F11)
                    {
                        SDL_ShowCursor(SDL_ENABLE);
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        catchMouse = false;
                    }
                    else if (event.key.keysym.scancode == SDL_SCANCODE_F12)
                    {
                        SDL_ShowCursor(SDL_DISABLE);
                        SDL_SetRelativeMouseMode(SDL_TRUE);
                        catchMouse = true;
                    }
                    else
                        camera.CheckInput(SDL_KEYDOWN, event.key.keysym.scancode);
                    break;
                case SDL_KEYUP:
                    camera.CheckInput(SDL_KEYUP, event.key.keysym.scancode);
                    break;
                case SDL_MOUSEMOTION:
                    if (catchMouse)
                        camera.checkInputMouse(event.motion.xrel, event.motion.yrel);
                default:
                    break;
            }
        }

        draw(window, &camera, sky, &sun, lights, &brushObjects);
    }

    SDL_Quit();
    return 0;
}
