//  Default fragment shader
#version 330

struct Material
{
   vec3 color;
   vec3 specular;
   float shininess;
};

uniform Material material;

out vec4 FragColor;

void main()
{
   FragColor = vec4(material.color, 1.0);
}
