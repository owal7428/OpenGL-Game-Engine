#ifndef CAMERA_H
#define CAMERA_H

#include "../../../Common.h"

#include "../GameObject.hpp"
#include "../../Utility/util.h"

class Camera : public GameObject
{
private:
    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 lookingAt;

    float fov, asp, zNear, zFar;
    int movementSpeed;
    int cameraSpeed;

    // Internal rotation angles
    float th, ph;
    float mouseMoveX, mouseMoveY;

    // Variables used to check if movement keys are pressed
    bool wKeyDown, sKeyDown, aKeyDown, dKeyDown, spaceKeyToggle;

    // Variables used to check if arrow keys are pressed
    bool upKeyDown, downKeyDown, leftKeyDown, rightKeyDown;

    void checkInputUp(SDL_Scancode code);
    void checkInputDown(SDL_Scancode code);

public:
    Camera(float fov, float asp, float zNear, float zFar, int movementSpeed, int cameraSpeed);

    /* Updates the projection matrix.
    *  @param fov field of view that the camera should have.
    *  @param asp aspect ratio of the view fustrum. */
    void UpdateProjection(float fov, float asp, float zNear, float zFar);

    /* Sets the position of the camera and the point at which the camera should look.
    *  @param Pos world coordinates of the camera.
    *  @param LookAt world coordinates of the point the camera should be looking at. */
    void LookAt(glm::vec3 lookAt);

    /* Returns the viewn matrix for the camera. */
    inline glm::mat4 getViewMatrix() {return view;}
    
    /* Returns the projection matrix for the camera. */
    inline glm::mat4 getProjectionMatrix() {return projection;}

    inline glm::vec3 getLookingAt() {return lookingAt;}

    void Move(glm::vec3 newPosition);
    void Update(double deltaTime);

    /* Checks for input from keyboard.
    *  @param type type of input (button down or up).
    *  @param code button that was pressed. */
    void CheckInput(uint32_t type, SDL_Scancode code);
    
    void checkInputMouse(int xRel, int yRel);
};

#endif // CAMERA_H
