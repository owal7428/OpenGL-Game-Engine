#include "Shader.hpp"

#include "Utility/util.h"

static const char* fileRead(const std::string& filePath)
{
    std::ifstream fStream(filePath);

    if (!fStream) Fatal("Cannot open shader %s\n", filePath);

    std::string line;
    std::stringstream ss;

    while (std::getline(ss, line))
    {
        ss << line << '\n';
    }

    fStream.close();

    std::string tempStr = ss.str();
    return tempStr.c_str();
}

Shader::Shader(const std::string& shaderPaths)
{
    ID = glCreateProgram();

    // Read contents of shaders
    const char* vertexCode = fileRead(shaderPaths + ".vert");
    const char* fragCode = fileRead(shaderPaths + ".frag");

    int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragCode, NULL);
    glCompileShader(frag);

    glAttachShader(ID, vertex);
    glAttachShader(ID, frag);

    glLinkProgram(ID);

    glDeleteShader(vertex);
    glDeleteShader(frag);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}

void Shader::Activate()
{
    glUseProgram(ID);
}

void Shader::Deactivate()
{
    // Switches to fixed pipeline
    glUseProgram(0);
}
