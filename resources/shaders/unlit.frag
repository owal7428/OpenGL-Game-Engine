//  Default fragment shader
#version 330

in vec2 TexCoordinate;

// Material properties
struct Material
{
   vec3 color;
   vec3 specular;
   float shininess;

   float ambientIntensity;
};

uniform Material material;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   FragColor = texture(TexFile, TexCoordinate) * vec4(material.color, 1.0);
}
