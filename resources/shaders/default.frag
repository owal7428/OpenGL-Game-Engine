//  Default fragment shader
#version 330

in vec2 TexCoordinate;

// Color for the vertex
uniform vec4 vertexColor;

// Properties of the light
uniform vec3 lightColor;

// Lighting variables
uniform float ambientStrength;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   vec3 ambient = lightColor * ambientStrength;
   FragColor = texture(TexFile, TexCoordinate) * vertexColor * vec4(ambient, 1.0);
}
