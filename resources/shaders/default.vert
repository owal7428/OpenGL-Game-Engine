//  Default vertex shader
#version 330

layout (location = 0) in vec3 vertexPosition;
layout (location = 2) in vec2 textureCoordinate;

// Model View Projection matrix
uniform mat4 MVP;

out vec2 TexCoordinate;

void main()
{
   //  Set vertex coordinates
   gl_Position = MVP * vec4(vertexPosition, 1.0);
   TexCoordinate = textureCoordinate;
}
