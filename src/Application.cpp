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
#define STEEL "resources/textures/steel.bmp"
#define WATER "resources/textures/water.bmp"

#define SKYBOX_FRONT "resources/textures/skybox/front.bmp"
#define SKYBOX_BACK "resources/textures/skybox/back.bmp"
#define SKYBOX_LEFT "resources/textures/skybox/left.bmp"
#define SKYBOX_RIGHT "resources/textures/skybox/right.bmp"
#define SKYBOX_TOP "resources/textures/skybox/top.bmp"
#define SKYBOX_BOTTOM "resources/textures/skybox/bottom.bmp"

double asp = 1;
double zFar = 30;
double fov = 90;

void GenerateSkybox(Plane* sky[], glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
    sky[0] -> Move(cameraPosition + glm::vec3(zFar, 0, 0));
    sky[0] -> Draw(cameraPosition, projectionMatrix, viewMatrix);
    
    sky[1] -> Move(cameraPosition - glm::vec3(zFar, 0, 0));
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

    Camera camera = Camera(fov, asp, 0.25, zFar / Cos(fov), 5, 5);
    
    reshape(window, &camera);

    ErrCheck("init");
                                                            // Position     // Rotation     // Scale
    Plane SkyboxRight = Plane(&unlitShader, SKYBOX_RIGHT,    zFar, 0, 0,     0, 90, 0,       zFar*2, zFar*2, zFar*2);
    Plane SkyboxLeft = Plane(&unlitShader,  SKYBOX_LEFT,     -zFar, 0, 0,    0, -90., 0,     zFar*2, zFar*2, zFar*2);
    Plane SkyboxTop = Plane(&unlitShader,   SKYBOX_TOP,      0, zFar, 0,     -90., 0, 0,     zFar*2, zFar*2, zFar*2);
    Plane SkyboxBottom = Plane(&unlitShader,SKYBOX_BOTTOM,   0, -zFar, 0,    90, 0, 0,       zFar*2, zFar*2, zFar*2);
    Plane SkyboxFront = Plane(&unlitShader, SKYBOX_FRONT,    0, 0, zFar,     0, 0, 0,        zFar*2, zFar*2, zFar*2);
    Plane SkyboxBack = Plane(&unlitShader,  SKYBOX_BACK,     0, 0, -zFar,    0, 180, 0,      zFar*2, zFar*2, zFar*2);

    Plane* sky[6] = {&SkyboxRight, &SkyboxLeft, &SkyboxTop, &SkyboxBottom, &SkyboxFront, &SkyboxBack};

    // Define objects in the scene
    Star bigStar        =   Star(&defaultShader, WOOD, -2, 0, -2, 0, 0, 20, 1, 1, 1);
    Star bigStarSingle  =   Star(&defaultShader, WOOD, 0, 0, 0, 0, -35, 0, 1, 1, 1);
    Star spinningStar   =   Star(&defaultShader, WOOD, 2, 1, -2, 0, -35, 0, 0.3, 0.3, 0.3);
    Star rotatingStar   =   Star(&defaultShader, STEEL, 1, 0, -2, 0, 0, 0, 0.15, 0.15, 0.15);
    Star otherStar      =   Star(&defaultShader,STEEL, 3, 1, -3, 0, 0, 0, 0.3, 0.3, 0.3);

    Rhombus rhombus         =   Rhombus(&defaultShader, WATER, -0.25, -1, 0.4, 0, 0, 0, 0.3, 0.6, 0.6);
    Rhombus rhombusSingle   =   Rhombus(&defaultShader, WATER, 0, 0, 0, 0.15, 0.3, 0.3, 1, 1, 1);

    Cube spinningStarCube   =   Cube(&unlitShader_untextured, 2, 1, -2, 0, 0, 0, 1, 1, 1);
    Cube rotatingStarCube   =   Cube(&unlitShader_untextured, 1, 0, -2, 0, 0, 0, 0.7, 0.7, 0.7);
    Cube rhombusCube        =   Cube(&unlitShader_untextured, -0.25, -1.0, 0.4, 0.0, 0, 0, 0.8, 0.8, 1);
    Cube rhombusCubeSingle  =   Cube(&unlitShader_untextured, 0, 0, 0, 0, 0, 0, 0.8, 0.8, 0.8);

    Plane testFloor = Plane(&defaultShader, WOOD, 0, -2, 0, -90, 0, 0, 20, 20, 20);
    testFloor.setTextureScale(5);

    Cube light = Cube(&unlitShader_untextured, 0, 0, 5, 0, 0, 0, 0.5, 0.5, 0.5);
    light.setColor(1,1,1);

    DirectionalLight sun = DirectionalLight(0, -0.5, -1, 0.86, 0.63, 0.34, 0.33, 0.70, 0.86, 1.0, 1.0, 1.0);

    PointLight light1 = PointLight(0, 0, 5, 1, 1, 1, 1.0, 1.0, 1.0, 0.75, 0.07, 0.017);

    std::vector<PointLight*> lights;
    lights.push_back(&light1);

    light.AddChild(&light1);

    Plane testPlane = Plane(&unlitShader_untextured, 3, 0, 0, 0, 45, 0, 1, 1, 1);
    testPlane.Rotate(glm::angleAxis(glm::radians(90.0f), glm::normalize(glm::vec3(1, 0, -1))));

    Cube testCube = Cube(&unlitShader_untextured, 4, 0, 2, 45, 45, 0, 2, 1, 1);

    Cube playerCollider = Cube(&unlitShader_untextured, 0, -1, 0, 0, 0, 0, 1, 2, 1);
    playerCollider.setColor(0,1,0);
    playerCollider.EnableRenderWireframe();

    camera.AddChild(&playerCollider);

    PlaneCollider testCollider = PlaneCollider(&camera, testPlane.getPosition(), testPlane.getRotation(), testPlane.getScale());
    BoxCollider testBoxCollider = BoxCollider(&camera, testCube.getPosition(), testCube.getRotation(), testCube.getScale());

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

    brushObjects1.push_back(&playerCollider);

    std::vector<Brush*> brushObjects2;
    
    brushObjects2.push_back(&rhombusSingle);
    brushObjects2.push_back(&rhombusCubeSingle);
    brushObjects2.push_back(&testFloor);
    brushObjects2.push_back(&light);

    brushObjects2.push_back(&testPlane);
    brushObjects2.push_back(&testCube);

    brushObjects2.push_back(&playerCollider);

    std::vector<Brush*> brushObjects3;
    
    brushObjects3.push_back(&bigStarSingle);
    
    brushObjects3.push_back(&light);

    brushObjects3.push_back(&playerCollider);

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
            Update();

            camera.Update(deltaTime);
            
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
            
            testPlane.Rotate(glm::angleAxis(glm::radians(90.0f), glm::normalize(glm::vec3(1, 0, -1))));
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
                    else
                        camera.CheckInput(SDL_KEYDOWN, event.key.keysym.scancode);
                    break;
                case SDL_KEYUP:
                    camera.CheckInput(SDL_KEYUP, event.key.keysym.scancode);
                    break;
                default:
                    break;
            }
        }

        glm::vec3 pos = camera.getPosition();

        testCollider.CollisionTest(glm::vec3(pos.x, pos.y, pos.z));
        testBoxCollider.CollisionTest(glm::vec3(pos.x, pos.y, pos.z));

        draw(window, &camera, sky, &sun, lights, &brushObjects2);
    }

    SDL_Quit();
    return 0;
}
