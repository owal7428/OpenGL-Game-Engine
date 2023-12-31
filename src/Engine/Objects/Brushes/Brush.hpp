#ifndef BRUSH_H
#define BRUSH_H

#include "../../../Common.h"

#include "../GameObject.hpp"

#include "../../VertexArray.hpp"
#include "../../Texture.hpp"
#include "../../Shader.hpp"

#include "../Entities/Lights/DirectionalLight.hpp"
#include "../Entities/Lights/PointLight.hpp"

typedef struct
{
    glm::vec3 color;
    glm::vec3 specular;
    int shininess;

    float textureScaleX;
    float textureScaleY;

} Material;

class Brush : public GameObject
{
protected:
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

    //std::vector<int> temp;
    
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

    void Draw(glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix, DirectionalLight* sun, std::vector<PointLight*> pointLights);
    void Draw(glm::vec3 cameraPosition, glm::mat4 projectionMatrix, glm::mat4 viewMatrix);

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

    inline void setTextureScale(float newScale) {material.textureScaleX = newScale; material.textureScaleY = newScale;}

    inline void setTextureScaleX(float newScale) {material.textureScaleX = newScale;}
    inline void setTextureScaleY(float newScale) {material.textureScaleY = newScale;}

    /* Enables wireframe rendering mode. */
    inline void EnableRenderWireframe() {drawWireFrame = true;}
    /* Disables wireframe rendering mode. */
    inline void DisableRenderWireframe() {drawWireFrame = false;}

    inline glm::quat getRotation() {return externalRotations * rotation;}
    inline glm::vec3 getScale() {return scale;}
};

#endif // BRUSH_H
