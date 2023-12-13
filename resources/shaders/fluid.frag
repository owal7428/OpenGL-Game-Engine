//  Fluid fragment shader
#version 330

in vec2 TexCoordinate;

in float xPos;
in float zPos;

// Material properties
struct Material
{
   float textureScaleX;
   float textureScaleY;
};

uniform Material material;

uniform float time;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   float ampX = 0.25 * 1.0 / material.textureScaleY;
   float ampY = 0.25 * 1.0 / material.textureScaleX;

   float newTexCoordinateX = TexCoordinate.x + (ampX * cos(time - zPos));
   float newTexCoordinateY = TexCoordinate.y + (ampY * cos(time - xPos));

   FragColor = texture(TexFile, vec2(newTexCoordinateX * material.textureScaleX, newTexCoordinateY * material.textureScaleY)) * vec4(1.0);
}