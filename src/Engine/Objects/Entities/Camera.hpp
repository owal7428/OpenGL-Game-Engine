#ifndef CAMERA_H
#define CAMERA_H

#include "../../../Common.h"
#include "../../Utility/util.h"

class Camera
{
private:
    glm::mat4 view_projection;

    glm::mat4 view;
    glm::mat4 projection;

    glm::vec3 location;
    glm::vec3 lookingAt;

    int fov, asp, zNear, zFar;
    int movementSpeed;
    int cameraSpeed;

    // Internal rotation angles
    float th, ph;

    // Variables used to check if movement keys are pressed
    bool wKeyDown, sKeyDown, aKeyDown, dKeyDown;

    // Variables used to check if arrow keys are pressed
    bool upKeyDown, downKeyDown, leftKeyDown, rightKeyDown;

    void updateViewProjection();

    void checkInputUp(SDL_Scancode code);
    void checkInputDown(SDL_Scancode code);

public:
    Camera(int fov, int asp, int zNear, int zFar, int movementSpeed, int cameraSpeed);

    /* Sets the position of the camera and the point at which the camera should look.
    *  @param Pos world coordinates of the camera.
    *  @param LookAt world coordinates of the point the camera should be looking at. */
    void LookAt(double xPos, double yPos, double zPos, double xLookAt, double yLookAt, double zLookAt);

    /* Updates the projection matrix.
    *  @param fov field of view that the camera should have.
    *  @param asp aspect ratio of the view fustrum. */
    void UpdateProjection(int fov, int asp, int zNear, int zFar);

    /* Returns the multiplied view-projection matrix for the camera. */
    inline glm::mat4 getMatrix() {return view_projection;}

    void Update(double deltaTime);

    /* Checks for input from keyboard.
    *  @param type type of input (button down or up).
    *  @param code button that was pressed. */
    void CheckInput(uint32_t type, SDL_Scancode code);
};

#endif // CAMERA_H
