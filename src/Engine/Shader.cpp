#include "Shader.hpp"

#include "Utility/util.h"

std::string fileRead(const std::string& filePath)
{
    std::ifstream fStream(filePath);

    if (!fStream) Fatal("Cannot open shader %s\n", filePath.c_str());

    std::string line;
    std::stringstream ss;

    while (std::getline(fStream, line))
    {
        ss << line << '\n';
    }

    fStream.close();

    std::string str = ss.str();
    return str;
}

static void PrintShaderLog(int obj, const std::string& filePath)
{
	const char* file = filePath.c_str();

	int length = 0;
	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &length);

	if (length > 1)
	{
		char* buffer = (char *)malloc(length);
		int bufferLength = 0;
		glGetShaderInfoLog(obj, length, &bufferLength, buffer);

		fprintf(stderr, "%s:\n%s\n", file, buffer);

		free(buffer);
	}

	glGetShaderiv(obj, GL_COMPILE_STATUS, &length);

	if (!length) Fatal("Error compiling %s\n", file);
}

/*
 *  Print Program Log
 */
static void PrintProgramLog(int obj)
{
	int length = 0;
	glGetProgramiv(obj, GL_INFO_LOG_LENGTH, &length);

	if (length > 1)
	{
		char* buffer = (char *)malloc(length);
		int bufferLength = 0;
		glGetProgramInfoLog(obj, length, &bufferLength, buffer);

		fprintf(stderr, "%s\n", buffer);

		free(buffer);
	}

	glGetProgramiv(obj, GL_LINK_STATUS, &length);

	if (!length) Fatal("Error linking program\n");
}

Shader::Shader(const std::string& shaderPaths)
{
    ID = glCreateProgram();

    // Read contents of shaders
    std::string vertexCodeTemp = fileRead(shaderPaths + ".vert");
    std::string fragCodeTemp = fileRead(shaderPaths + ".frag");

	const char* vertexCode = vertexCodeTemp.c_str();
	const char* fragCode = fragCodeTemp.c_str();

    int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexCode, NULL);
    glCompileShader(vertex);

    PrintShaderLog(vertex, shaderPaths + ".vert");

    int frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &fragCode, NULL);
    glCompileShader(frag);

    PrintShaderLog(frag, shaderPaths + ".frag");

    glAttachShader(ID, vertex);
    glAttachShader(ID, frag);

    glLinkProgram(ID);

    PrintProgramLog(ID);

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

void Shader::setUniform1f(const std::string& uniformName, float value)
{
    int temp = glGetUniformLocation(getID(), uniformName.c_str());
    glUniform1f(temp, value);
}

void Shader::setUniform1i(const std::string& uniformName, int value)
{
    int temp = glGetUniformLocation(getID(), uniformName.c_str());
    glUniform1i(temp, value);
}

void Shader::setUniform3f(const std::string& uniformName, float value1, float value2, float value3)
{
    int temp = glGetUniformLocation(getID(), uniformName.c_str());
    glUniform3f(temp, value1, value2, value3);
}

void Shader::setUniform4f(const std::string& uniformName, float value1, float value2, float value3, float value4)
{
    int temp = glGetUniformLocation(getID(), uniformName.c_str());
    glUniform4f(temp, value1, value2, value3, value4);
}

void Shader::setUniformMat4(const std::string& uniformName, glm::mat4* matrix)
{
    int temp = glGetUniformLocation(getID(), uniformName.c_str());
    glUniformMatrix4fv(temp, 1, GL_FALSE, glm::value_ptr(*matrix));
}
