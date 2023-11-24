//  Default fragment shader
#version 330

// Color for the vertex
uniform vec4 vertexColor;

out vec4 FragColor;

void main()
{
   FragColor = vertexColor;
}
