//  Default fragment shader
#version 330

in vec2 TexCoordinate;

// Color for the vertex
uniform vec4 vertexColor;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   vec4 tex = texture(TexFile, TexCoordinate);

   float texVisibleX = 1 - step(tex.x, 0.0001);
   float texVisibleY = 1 - step(tex.y, 0.0001);
   float texVisibleZ = 1 - step(tex.z, 0.0001);

   float colorX = (tex.x * texVisibleX) + (vertexColor.x * (1 - texVisibleX));
   float colorY = (tex.y * texVisibleY) + (vertexColor.y * (1 - texVisibleY));
   float colorZ = (tex.z * texVisibleZ) + (vertexColor.z * (1 - texVisibleZ));

   FragColor = vec4(colorX, colorY, colorZ, 1.0);
}
