#ifndef BRUSH_H
#define BRUSH_H

#include "../../../Common.h"

#include "../../VertexArray.hpp"
#include "../../Texture.hpp"
#include "../../Shader.hpp"

typedef struct
{
    glm::vec3 color;
    glm::vec3 specular;
    int shininess;

    float textureScale;

} Material;

class Brush
{
protected:
    glm::vec3 position;
    glm::vec3 scale;

    // Rotation given as a quaternion for easy use with arbitrary rotation axies
    glm::quat rotation;
    glm::quat externalRotations;

    VertexArray* VAO;
    int primitiveType;
    int numVertices;

    Texture* texture;
    bool hasTexture;
    bool drawWireFrame;

    Shader* shader;
    Material material;

    std::vector<int> temp;
    
public:
    Brush() {}

    // Textured constructor
    Brush(Shader* shaderFile, const char* textureFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);

    // Non-textured constructor
    Brush(Shader* shaderFile,
          float x, float y, float z,
          float rot_x, float rot_y, float rot_z,
          float scale_x, float scale_y, float scale_z);
    
    ~Brush();

    void Draw(glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, glm::vec3 lightPosition, glm::vec3 lightColor);

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

    void setColor(float r, float g, float b) {material.color = glm::vec3(r, g, b);}
    
    void setMaterial(Material newMaterial) {material = newMaterial;}

    inline void setShader(Shader* newShader) {shader = newShader;}

    inline void setTextureScale(float newScale) {material.textureScale = newScale;}

    /* Enables wireframe rendering mode. */
    inline void EnableRenderWireframe() {drawWireFrame = true;}
    /* Disables wireframe rendering mode. */
    inline void DisableRenderWireframe() {drawWireFrame = false;}

    inline glm::vec3 getPosition() {return position;}
    inline glm::quat getRotation() {return rotation;}
};

#endif // BRUSH_H
