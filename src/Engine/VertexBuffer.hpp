#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "../Common.h"

class VertexBuffer
{
private:
    unsigned int ID;

public:
    VertexBuffer(std::vector<float>* vertices);
    ~VertexBuffer();

    void Bind();
    void Unbind();
};

#endif // VERTEX_BUFFER_H
