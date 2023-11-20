#include "Camera.hpp"

Camera::Camera(int fov, int asp, int zNear, int zFar, int movementSpeed, int cameraSpeed)
{
    this -> fov     = fov;
    this -> asp     = asp;
    this -> zNear   = zNear;
    this -> zFar    = zFar;

    th = 0;
    ph = 0;

    this -> movementSpeed = movementSpeed;
    this -> cameraSpeed = cameraSpeed;

    location = glm::vec3(0.0f, 0.0f, 0.0f);
    lookingAt = glm::vec3(0.0f, 0.0f, 1.0f);

    wKeyDown = false;
    sKeyDown = false;
    aKeyDown = false;
    dKeyDown = false;

    upKeyDown = false;
    downKeyDown = false;
    leftKeyDown = false;
    rightKeyDown = false;

    LookAt(0, 0, 0, 0, 0, 1);
    UpdateProjection(fov, asp, zNear, zFar);
}

void Camera::updateViewProjection()
{
    view_projection = projection * view;
}

void Camera::UpdateProjection(int fov, int asp, int zNear, int zFar)
{
    projection = glm::perspective(fov, asp, zNear, zFar);

    updateViewProjection();
}

void Camera::LookAt(double xPos, double yPos, double zPos, double xLookAt, double yLookAt, double zLookAt)
{
    glm::vec3 eye = glm::vec3(xPos, yPos, -zPos);
    glm::vec3 center = glm::vec3(xLookAt, yLookAt, -zLookAt);

    view = glm::lookAt(eye, center, glm::vec3(0, 1, 0));

    updateViewProjection();
}

void Camera::Update(double deltaTime)
{
    float newTh = th;
    float newPh = ph;

    // Check if keys are pressed down If yes, continue rotating.
    if (!rightKeyDown || !leftKeyDown)
    {
        if (rightKeyDown)
            newTh += cameraSpeed * deltaTime;
        else if (leftKeyDown)
            newTh -= cameraSpeed * deltaTime;
    }
    if (!upKeyDown || !downKeyDown)
    {
        if (upKeyDown)
            newPh += cameraSpeed * deltaTime;
        else if (downKeyDown)
            newPh -= cameraSpeed * deltaTime;
    }
    
    while (th >= 360)
        newTh -= 360;
    
    // Make sure can't go upside down
    if (ph > 90)
        newPh = 90;

    else if (ph < -90)
        newPh = -90;
    
    // Only update looking at vector when angles change
    if (newTh != th || newPh != ph)
    {
        th = newTh;
        ph = newPh;

        float newLookingAtX = glm::sin(glm::radians(th)) * glm::cos(glm::radians(ph));
        float newLookingAtY = glm::sin(glm::radians(ph));
        float newLookingAtZ = glm::cos(glm::radians(th)) * glm::cos(glm::radians(ph));

        lookingAt = glm::vec3(newLookingAtX, newLookingAtY, newLookingAtZ);
    }

    // Check if wasd keys are pressed down
    if (!wKeyDown || !sKeyDown)
    {
        float newX = lookingAt.x * movementSpeed * deltaTime;
        float newY = lookingAt.y * movementSpeed * deltaTime;
        float newZ = lookingAt.z * movementSpeed * deltaTime;

        if (wKeyDown)
        {
            location += glm::vec3(newX, newY, newZ);
        }
        else if (sKeyDown)
        {
            location -= glm::vec3(newX, newY, newZ);
        }
    }
    if (!aKeyDown || !dKeyDown)
    {
        float xOffset = glm::sin(glm::radians(90 - th)) * movementSpeed * deltaTime;
        float zOffset = glm::cos(glm::radians(90 - th)) * movementSpeed * deltaTime;

        glm::vec3 offset = glm::vec3(xOffset, 0, -zOffset);

        if (aKeyDown)
        {
            location += offset;
        }
        else if (dKeyDown)
        {
            location -= offset;
        }
    }

    LookAt(location.x, location.y, location.z, lookingAt.x, lookingAt.y, lookingAt.z);
}

void Camera::CheckInput(uint32_t type, SDL_Scancode code)
{
    if (type == SDL_KEYDOWN)
        checkInputDown(code);

    else if (type == SDL_KEYUP)
        checkInputUp(code);
}

void Camera::checkInputDown(SDL_Scancode code)
{
    switch (code)
    {
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

void Camera::checkInputUp(SDL_Scancode code)
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
