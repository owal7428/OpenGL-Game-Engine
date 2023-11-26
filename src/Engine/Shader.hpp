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

    /* Links uniform of type float to shader.
    *  @param uniformName name of the uniform in the shader.
    *  @param value float value to link to shader. */
    void setUniform1f(const std::string& uniformName, float value);

    /* Links uniform of type int to shader.
    *  @param uniformName name of the uniform in the shader.
    *  @param value integer value to link to shader. */
    void setUniform1i(const std::string& uniformName, int value);
    
    /* Links uniform of type vec3 to shader.
    *  @param uniformName name of the uniform in the shader.
    *  @param value* values in the vec3 to link to shader. */
    void setUniform3f(const std::string& uniformName, float value1, float value2, float value3);

    /* Links uniform of type vec4 to shader.
    *  @param uniformName name of the uniform in the shader.
    *  @param value* values in the vec4 to link to shader. */
    void setUniform4f(const std::string& uniformName, float value1, float value2, float value3, float value4);

    /* Links uniform of type mat4 to shader.
    *  @param uniformName name of the uniform in the shader.
    *  @param matrix pointer to matrix to link to shader. */
    void setUniformMat4(const std::string& uniformName, glm::mat4* matrix);

    inline unsigned int getID() {return ID;}
};

#endif // SHADER_H
