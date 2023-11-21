#include "VertexBuffer.hpp"

#include "Utility/util.h"

VertexBuffer::VertexBuffer(std::vector<float>* vertices)
{
    glGenBuffers(1, &ID);
    
    Bind();
    
    glBufferData(GL_ARRAY_BUFFER, (*vertices).size() * sizeof(float), (*vertices).data(), GL_STATIC_DRAW);

    //  Define vertexes
    glVertexPointer(3, GL_FLOAT, 8 * sizeof(float), (void*) 0);
    glEnableClientState(GL_VERTEX_ARRAY);

    // Define normals
    glNormalPointer(GL_FLOAT, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableClientState(GL_NORMAL_ARRAY);

    // Define texture coordinates
    glTexCoordPointer(2, GL_FLOAT, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    Unbind();
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VertexBuffer::Unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
