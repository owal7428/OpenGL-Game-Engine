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

   float textureScaleX;
   float textureScaleY;
};

uniform Material material;

struct DirectionalLight
{
   vec3 direction;
   
   vec3 color;
   vec3 ambient;
   vec3 specular;
};

uniform DirectionalLight sun;

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

uniform PointLight pointLights[7];

uniform sampler2D TexFile;

out vec4 FragColor;

vec3 renderDirectionalLight(DirectionalLight light, vec3 n_Normal, vec3 viewDirection);
vec3 renderPointLight(PointLight light, vec3 n_Normal, vec3 viewDirection);

void main()
{
   vec3 n_Normal        = normalize(Normal);
   vec3 viewDirection   = normalize(cameraPosition - VertexPos);

   vec3 lighting = renderDirectionalLight(sun, n_Normal, viewDirection);

   for (int i = 0; i < 7; i++)
      lighting += max(renderPointLight(pointLights[i], n_Normal, viewDirection), 0.0);

   FragColor = texture(TexFile, vec2(TexCoordinate.x * material.textureScaleX, TexCoordinate.y * material.textureScaleY) ) * vec4(lighting, 1.0);
}

vec3 renderDirectionalLight(DirectionalLight light, vec3 n_Normal, vec3 viewDirection)
{
   vec3 l_direction = normalize(-light.direction);

   // Calculate diffuse
   vec3 diffuse = max(dot(n_Normal, l_direction), 0.0) * light.color * material.color;

   // Calculate specular
   vec3 reflection      = reflect(-l_direction, n_Normal);
   vec3 specular       = pow(max(dot(viewDirection, reflection), 0.0), material.shininess) * material.specular * light.color;

   return (0.25 * light.ambient) + diffuse + specular;
}

vec3 renderPointLight(PointLight light, vec3 n_Normal, vec3 viewDirection)
{
   vec3 l_direction  = normalize(light.position - VertexPos);

   // Calculate diffuse
   vec3 diffuse = max(dot(n_Normal, l_direction), 0.0) * light.color * material.color;

   // Calculate specular
   vec3 reflection      = reflect(-l_direction, n_Normal);
   vec3 specular       = pow(max(dot(viewDirection, reflection), 0.0), material.shininess) * material.specular * light.color;

   float dist = length(light.position - VertexPos);
   float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

   diffuse *= attenuation;
   specular *= attenuation;

   return diffuse + specular;
}
