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
   int shininess;
};

uniform Material material;

// Light properties
struct PointLight
{
   vec3 position;
   
   vec3 color;
   vec3 specular;

   float constant;
   float linear;
   float quadratic;
};

uniform PointLight pointLights[4];

uniform sampler2D TexFile;

out vec4 FragColor;

vec3 renderPointLight(PointLight light, vec3 n_Normal, vec3 viewDirection);

void main()
{
   vec3 n_Normal        = normalize(Normal);
   vec3 viewDirection   = normalize(cameraPosition - VertexPos);

   vec3 lighting = renderPointLight(pointLights[0], n_Normal, viewDirection);

   FragColor = texture(TexFile, TexCoordinate) * vec4(lighting, 1.0);
}

vec3 renderPointLight(PointLight light, vec3 n_Normal, vec3 viewDirection)
{
   vec3 l_direction  = normalize(light.position - VertexPos);
   float faceAligned = max(dot(n_Normal, l_direction), 0.0);

   // Calculate diffuse
   vec3 diffuse = faceAligned * light.color * material.color;

   // Calculate specular
   vec3 reflection      = reflect(-l_direction, n_Normal);
   vec3 specular       = pow(max(dot(viewDirection, reflection), 0.0), material.shininess) * material.specular * light.color;

   float dist = length(light.position - VertexPos);
   float attenuation = 1.0 / (light.constant, + light.linear * dist + light.quadratic * (dist * dist));

   diffuse *= attenuation;
   specular *= attenuation;

   return diffuse + specular;
}
