//  Default fragment shader
#version 330

in vec2 TexCoordinate;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   FragColor = texture(TexFile, TexCoordinate) * vec4(1.0);
}
