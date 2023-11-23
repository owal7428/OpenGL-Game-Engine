#ifndef SHADER_H
#define SHADER_H

#include "../Common.h"

class Shader
{
private:
    unsigned int ID;

public:
    /* Constructs and compiles shaders into a shader program.
    *  @param filePath path to shaders (should not include .frag or .vert extension) */
    Shader(const std::string& filePath);
    ~Shader();

    void Activate();
    void Deactivate();

    inline unsigned int getID() {return ID;}
};

#endif // SHADER_H
