//  Default vertex shader
#version 330

layout (location = 0) in vec3 vertexPosition;

// Model View Projection matrix
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   //  Set vertex coordinates
   gl_Position = projection * view * model * vec4(vertexPosition, 1.0);
}
