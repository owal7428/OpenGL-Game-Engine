//  Default fragment shader
#version 330

in vec3 VertexPos;

in vec3 Normal;
in vec2 TexCoordinate;

uniform vec3 cameraPosition;

// Color for the vertex
uniform vec4 vertexColor;

// Properties of the light
uniform vec3 lightPos;
uniform vec3 lightColor;

// Lighting variables
uniform float ambientIntensity;
float specularStrength = 0.2;
int shinyness = 32;

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

   // Calculate specular
   vec3 viewDirection   = normalize(cameraPosition - VertexPos);
   vec3 reflection      = reflect(-direction, nNormal);
   float spec           = pow(max(dot(viewDirection, reflection), 0.0), shinyness);
   vec3 specular        = specularStrength * spec * lightColor;

   vec3 lighting = ambient + diffuse + specular;

   FragColor = texture(TexFile, TexCoordinate) * vertexColor * vec4(lighting, 1.0);
}
