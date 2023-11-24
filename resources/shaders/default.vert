//  Default vertex shader
#version 330

layout (location = 0) in vec3 vertexData;
layout (location = 1) in vec3 normalData;
layout (location = 2) in vec2 textureData;

// Model View Projection matrix
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 VertexPos;

out vec3 Normal;
out vec2 TexCoordinate;

void main()
{
   //  Set vertex coordinates
   gl_Position = projection * view * model * vec4(vertexData, 1.0);

   VertexPos = vec3(model * vec4(vertexData, 1.0));

   Normal = mat3(transpose(inverse(model))) * normalData;
   TexCoordinate = textureData;
}
