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


    DirectionalLight sun = DirectionalLight(0, -0.5, -1, 0.86, 0.63, 0.34, 0.33, 0.70, 0.86, 1.0, 1.0, 1.0);

    //PointLight light1 = PointLight(0, 0, 5, 1, 1, 1, 1.0, 1.0, 1.0, 0.75, 0.07, 0.017);

    std::vector<PointLight*> lights;

    // Define motor entities in the scene
    

    std::vector<Brush*> brushObjects;

    Cube floor = Cube(&defaultShader, BRICK2, 0, -2, 9.5, 0, 0, 0, 35, 2, 25);
    floor.setColor(1, 0.8, 0.7);
    floor.setTextureScale(5);
    brushObjects.push_back(&floor);

    Cube platform = Cube(&defaultShader, BRICK2, 0, 0.375, 0, 0, 0, 0, 35, 2.75, 6);
    platform.setTextureScaleY(2);
    platform.setTextureScaleX(5);
    brushObjects.push_back(&platform);

    std::vector<Collider*> colliders;

    BoxCollider floorCollider = BoxCollider(&camera, floor.getPosition(), floor.getRotation(), floor.getScale());
    colliders.push_back(&floorCollider);

    BoxCollider platformCollider = BoxCollider(&camera, platform.getPosition(), platform.getRotation(), platform.getScale());
    colliders.push_back(&platformCollider);

    std::vector<Motor*> motorObjects;



    std::vector<Rotator*> rotatorObjects;



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
            int brushListSize = brushObjects.size();
            
            for (int i = 0; i < brushListSize; i++)
                brushObjects.at(i)->ResetRotations();
            
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
