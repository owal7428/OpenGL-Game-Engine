#include "Camera.hpp"

Camera::Camera(float fov, float asp, float zNear, float zFar, int movementSpeed, int cameraSpeed)
{
    this -> fov     = fov;
    this -> asp     = asp;
    this -> zNear   = zNear;
    this -> zFar    = zFar;

    th = 0;
    ph = 0;

    mouseMoveX = 0;
    mouseMoveY = 0;

    this -> movementSpeed = movementSpeed;
    this -> cameraSpeed = cameraSpeed;

    this -> position = glm::vec3(0.0f, 0.0f, 0.0f);
    this -> lookingAt = glm::vec3(0.0f, 0.0f, 1.0f);

    wKeyDown = false;
    sKeyDown = false;
    aKeyDown = false;
    dKeyDown = false;
    spaceKeyToggle = false;

    upKeyDown = false;
    downKeyDown = false;
    leftKeyDown = false;
    rightKeyDown = false;

    noclip = false;

    view = glm::lookAt(position, position + lookingAt, glm::vec3(0, 1, 0));
    UpdateProjection(fov, asp, zNear, zFar);
}

void Camera::UpdateProjection(float fov, float asp, float zNear, float zFar)
{
    projection = glm::perspective(glm::radians(fov), asp, zNear, zFar);
}

void Camera::LookAt(glm::vec3 lookAt)
{
    lookingAt = glm::vec3(lookAt.x, lookAt.y, lookAt.z);
    
    view = glm::lookAt(position, position + lookAt, glm::vec3(0, 1, 0));
}

void Camera::Move(glm::vec3 newPosition)
{
    GameObject::Move(newPosition);
    LookAt(lookingAt);
}

void Camera::moveNormal(double deltaTime)
{
    velocity = glm::vec3(0, velocity.y, 0);

    glm::vec3 temp = glm::vec3(0,0,0);

    // Check if wasd keys are pressed down
    if (!wKeyDown || !sKeyDown)
    {
        float xOffset = glm::cos(glm::radians(90 - th));
        float zOffset = glm::sin(glm::radians(90 - th));

        glm::vec3 offset = glm::vec3(xOffset, 0, zOffset);

        if (wKeyDown)
        {
            temp += offset;
        }
        else if (sKeyDown)
        {
            temp -= offset;
        }
    }
    if (!aKeyDown || !dKeyDown)
    {
        float xOffset = glm::sin(glm::radians(90 - th));
        float zOffset = glm::cos(glm::radians(90 - th));

        glm::vec3 offset = glm::vec3(xOffset, 0, -zOffset);
        
        if (aKeyDown)
        {
            temp += offset;
        }
        else if (dKeyDown)
        {
            temp -= offset;
        }
    }

    if (temp != glm::vec3(0,0,0))
        temp = glm::normalize(temp);
    
    MoveVelocity(velocity + glm::vec3(temp.x * movementSpeed, 0, temp.z * movementSpeed));

    Move(position + glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, velocity.z * deltaTime));
}

void Camera::moveNoclip(double deltaTime)
{
    // Check if wasd keys are pressed down
    if (!wKeyDown || !sKeyDown)
    {
        float newX = lookingAt.x * movementSpeed * deltaTime;
        float newY = lookingAt.y * movementSpeed * deltaTime;
        float newZ = lookingAt.z * movementSpeed * deltaTime;

        if (wKeyDown)
        {
            Move(position + glm::vec3(newX, newY, newZ));
        }
        else if (sKeyDown)
        {
            Move(position - glm::vec3(newX, newY, newZ));
        }
    }
    if (!aKeyDown || !dKeyDown)
    {
        float xOffset = glm::sin(glm::radians(90 - th)) * movementSpeed * deltaTime;
        float zOffset = glm::cos(glm::radians(90 - th)) * movementSpeed * deltaTime;

        glm::vec3 offset = glm::vec3(xOffset, 0, -zOffset);
        
        if (aKeyDown)
        {
            Move(position + offset);
        }
        else if (dKeyDown)
        {
            Move(position - offset);
        }
    }
}

void Camera::Update(double deltaTime)
{
    float newTh = th;
    float newPh = ph;

    // Check if keys are pressed down If yes, continue rotating.
    if (!rightKeyDown || !leftKeyDown)
    {
        if (rightKeyDown)
            newTh -= 10 * cameraSpeed * deltaTime;
        else if (leftKeyDown)
            newTh += 10 * cameraSpeed * deltaTime;
    }
    if (!upKeyDown || !downKeyDown)
    {
        if (upKeyDown)
            newPh += 10 * cameraSpeed * deltaTime;
        else if (downKeyDown)
            newPh -= 10 * cameraSpeed * deltaTime;
    }
    if (mouseMoveX != 0 || mouseMoveY != 0)
    {
        newTh -= mouseMoveX * cameraSpeed * deltaTime;
        newPh -= mouseMoveY * cameraSpeed * deltaTime;

        mouseMoveX = 0;
        mouseMoveY = 0;
    }
    
    while (newTh >= 360)
        newTh -= 360;
    
    while (newTh < 0)
        newTh += 360;
    
    // Make sure can't go upside down
    if (newPh > 89)
        newPh = 89;

    else if (newPh < -89)
        newPh = -89;
    
    // Only update looking at vector when angles change
    if (newTh != th || newPh != ph)
    {
        th = newTh;
        ph = newPh;

        float newLookingAtX = glm::sin(glm::radians(th)) * glm::cos(glm::radians(ph));
        float newLookingAtY = glm::sin(glm::radians(ph));
        float newLookingAtZ = glm::cos(glm::radians(th)) * glm::cos(glm::radians(ph));

        LookAt(glm::vec3(newLookingAtX, newLookingAtY, newLookingAtZ));
    }

    // Gravity
    MoveVelocity(velocity + glm::vec3(0, -9.8 * deltaTime, 0));

    if (velocity.y < -9.8)
        MoveVelocity(glm::vec3(velocity.x, -9.8, velocity.z));

    if (spaceKeyToggle)
    {
        MoveVelocity(velocity + glm::vec3(0, 4.5, 0));
        spaceKeyToggle = 0;
    }

    if (noclip)
        moveNoclip(deltaTime);
    else
        moveNormal(deltaTime);
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
        
        case SDL_SCANCODE_SPACE:
            spaceKeyToggle = 1;
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

void Camera::checkInputMouse(int xRel, int yRel)
{
    mouseMoveX += xRel;
    mouseMoveY += yRel;
}
