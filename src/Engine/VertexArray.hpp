#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include "../Common.h"

#include "VertexBuffer.hpp"

class VertexArray
{
private:
    unsigned int ID;
    VertexBuffer* VBO;

public:
    VertexArray(std::vector<float>* vertices);
    ~VertexArray();

    void Bind();
    void Unbind();
};

#endif // VERTEX_ARRAY_H
