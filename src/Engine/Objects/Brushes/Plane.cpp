#include "Plane.hpp"

#include "../../Utility/util.h"

// Vertex data for star object
static std::vector<float> vertexData = 
{
    // Front        // Normals      // Texture coordinates
    -1, -1, 0,      0, 0, 1,        0, 0,
    1, -1, 0,       0, 0, 1,        1, 0,
    1, 1, 0,        0, 0, 1,        1, 1,
    -1, 1, 0,       0, 0, 1,        0, 1,
};

const int numVertices = 4;

Plane::Plane(const char* textureFile,
             float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z) : Brush(textureFile, x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    // Do nothing for now
}

Plane::Plane(float x, float y, float z,
             float rot_x, float rot_y, float rot_z,
             float scale_x, float scale_y, float scale_z) : Brush(x, y, z, rot_x, rot_y, rot_z, scale_x, scale_y, scale_z)
{
    // Do nothing for now
}

void Plane::Draw(int emission, float shiny)
{
    float color_array[] = {color.x, color.y, color.z, 1};
    float black[] = {0, 0, 0, 1};
    
    glColor4fv(color_array);
    glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION, black);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE, color_array);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR, color_array);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, shiny);

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Define normals
    glNormalPointer(GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableClientState(GL_NORMAL_ARRAY);

    // Define texture coordinates
    glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    if (hasTexture)
    {
        //  Enable textures
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);

        texture -> Bind();
    }
    
    if (drawWireFrame)
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        glDisable(GL_LIGHTING);
    }

    glPushMatrix();

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, position);

    glm::mat4 model = glm::mat4(1.0f);
    model = model * glm::toMat4(externalRotations * rotation);
    model = glm::scale(model, scale);
    
    glMultMatrixf(glm::value_ptr(view * model));

    glDrawArrays(GL_QUADS, 0, numVertices);
    
    glPopMatrix();

    if (drawWireFrame)
    {
        glEnable(GL_LIGHTING);
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }

    if (hasTexture)
    {
        texture -> Unbind();
        glDisable(GL_TEXTURE_2D);
    }

    //  Disable vertex array
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
