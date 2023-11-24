//  Default vertex shader
#version 330

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec2 textureData;

// Model View Projection matrix
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoordinate;

void main()
{
   //  Set vertex coordinates
   gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
   TexCoordinate = textureData;
}
