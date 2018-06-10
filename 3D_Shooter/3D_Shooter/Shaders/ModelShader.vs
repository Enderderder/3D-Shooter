#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;

uniform mat4 model;
uniform mat3 normalMat;
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position, 1.0f);
	fragPos = vec3(model * vec4(position, 1.0));
	fragTexCoords = texCoords;
	fragNormal = normalMat * normal;
}