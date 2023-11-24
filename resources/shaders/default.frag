//  Default fragment shader
#version 330

in vec3 VertexPos;

in vec3 Normal;
in vec2 TexCoordinate;

// Color for the vertex
uniform vec4 vertexColor;

// Properties of the light
uniform vec3 lightPos;
uniform vec3 lightColor;

// Lighting variables
uniform float ambientIntensity;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   // Calculate ambient
   vec3 ambient = lightColor * ambientIntensity;

   // Calculate diffuse
   vec3 nNormal      = normalize(Normal);
   vec3 direction    = normalize(lightPos - VertexPos);
   vec3 diffuse      = max(dot(nNormal, direction), 0.0) * lightColor;

   vec3 lighting = min(ambient + diffuse, 1.0);

   FragColor = texture(TexFile, TexCoordinate) * vertexColor * vec4(lighting, 1.0);
}
