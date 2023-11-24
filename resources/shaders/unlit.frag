//  Default fragment shader
#version 330

in vec2 TexCoordinate;

// Color for the vertex
uniform vec4 vertexColor;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   FragColor = texture(TexFile, TexCoordinate) * vertexColor;
}
