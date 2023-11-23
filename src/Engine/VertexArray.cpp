#include "VertexArray.hpp"

#include "Utility/util.h"

VertexArray::VertexArray(std::vector<float>* vertices)
{
    glGenVertexArrays(1, &ID);

    Bind();

    VBO = new VertexBuffer(vertices);

    VBO -> Bind();

    // Define vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    // Define normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Define texture coordinates attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    VBO -> Unbind();

    Unbind();
}

VertexArray::~VertexArray()
{
    if (VBO != nullptr)
        delete VBO;
    
    glDeleteVertexArrays(1, &ID);
}

void VertexArray::Bind()
{
    glBindVertexArray(ID);
}

void VertexArray::Unbind()
{
    glBindVertexArray(0);
}
