//  Default fragment shader
#version 330

in vec2 TexCoordinate;

// Material properties
struct Material
{
   float textureScaleX;
   float textureScaleY;
};

uniform Material material;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   FragColor = texture(TexFile, vec2(TexCoordinate.x * material.textureScaleX, TexCoordinate.y * material.textureScaleY)) * vec4(1.0);
}
