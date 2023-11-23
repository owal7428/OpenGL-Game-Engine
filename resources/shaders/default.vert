//  Default vertex shader
#version 330

layout (location = 0) in vec3 vertexPosition;

// Model View Projection matrix
uniform mat4 MVP;

void main()
{
   //  Set vertex coordinates
   gl_Position = MVP * vec4(vertexPosition, 1.0);
}
