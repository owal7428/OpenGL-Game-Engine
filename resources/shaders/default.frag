//  Default fragment shader
#version 330

in vec3 VertexPos;

in vec3 Normal;
in vec2 TexCoordinate;

uniform vec3 cameraPosition;

// Material properties
struct Material
{
   vec3 color;
   vec3 specular;
   float shininess;

   float ambientIntensity;
};

uniform Material material;

// Light properties
struct Light
{
   vec3 position;
   
   vec3 color;
   vec3 specular;
};

uniform Light light;

uniform sampler2D TexFile;

out vec4 FragColor;

void main()
{
   // Calculate ambient
   vec3 ambient = material.ambientIntensity * light.color * material.color;

   // Calculate diffuse
   vec3 n_Normal      = normalize(Normal);
   vec3 l_direction   = normalize(light.position - VertexPos);
   vec3 diffuse       = max(dot(n_Normal, l_direction), 0.0) * light.color * material.color;

   // Calculate specular
   vec3 viewDirection   = normalize(cameraPosition - VertexPos);
   vec3 reflection      = reflect(-l_direction, n_Normal);
   vec3 specular       = pow(max(dot(viewDirection, reflection), 0.0), material.shininess) * material.specular * light.color;

   vec3 lighting = ambient + diffuse + specular;

   FragColor = texture(TexFile, TexCoordinate) * vec4(lighting, 1.0);
}
