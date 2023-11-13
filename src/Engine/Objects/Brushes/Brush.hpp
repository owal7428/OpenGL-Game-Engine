#ifndef BRUSH_H
#define BRUSH_H

#include "../../../Common.h"
#include "../../Texture.hpp"

class Brush
{
protected:
    glm::vec3 position;
    
    // Rotation given as a quaternion for easy use with arbitrary rotation axies
    glm::quat rotation;
    glm::quat externalRotations;

    glm::vec3 scale;

    bool hasTexture;

    Texture* texture;
    

public:
    Brush() {}

    // Textured constructor
    Brush(const char* textureFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);

    // Non-textured constructor
    Brush(float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
    
    ~Brush();

    void Draw(int emission, float shiny);

    /* Sets the position vector to new vector
    *  @param newPosition new vec3 to set position to. */
    void Move(glm::vec3 newPosition) {position = newPosition;}

    /* Adds rotation on top of the base orientation. Useful for external actors.
    *  @param newRotation quaternion representing rotation to add on top of external rotations. */
    void Rotate(glm::quat newRotation) {externalRotations = newRotation * externalRotations;}

    /* Resets external rotation quaternion to identity. Call this before applying external rotations from an actor. */
    void ResetRotations() {externalRotations = glm::quat(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));}

    /* Sets the base orientation of the object.
    *  @param newRotation quaternion representing rotation to set current rotation to. */
    void SetRotation(glm::quat newRotation) {rotation = newRotation;}

    inline glm::vec3 getPosition() {return position;}
    inline glm::quat getRotation() {return rotation;}

private:
    virtual void drawUntextured(int emission, float shiny) = 0;
    virtual void drawTextured(int emission, float shiny) = 0;
};

#endif // BRUSH_H
