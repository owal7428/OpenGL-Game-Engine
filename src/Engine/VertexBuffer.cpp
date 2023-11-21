#include "VertexBuffer.hpp"

#include "Utility/util.h"

VertexBuffer::VertexBuffer(std::vector<float>* vertices)
{
    glGenBuffers(1, &ID);
    
    Bind();
    
    glBufferData(GL_ARRAY_BUFFER, (*vertices).size() * sizeof(float), (*vertices).data(), GL_STATIC_DRAW);

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
