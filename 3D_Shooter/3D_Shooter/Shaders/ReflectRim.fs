#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;
uniform samplerCube cubeMap;

uniform vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
uniform vec3 camPos;
uniform vec3 rimColor;

void main()
{
	// Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 negViewDir = normalize(camPos - fragPos);
	vec3 viewDir = normalize(fragPos - camPos);
	vec3 reflectDir = reflect(viewDir, norm);

	// Rim Lighting
	float rimFactor = 1.0 - dot(norm, negViewDir);
	rimFactor = smoothstep(0.0, 1.0, rimFactor);
	rimFactor = pow(rimFactor, 2);
	vec3 rim = rimFactor * rimColor * lightColor;

	//color = vec4(rim, 1.0f) * texture(tex, fragTexCoord) * vec4(texture(cubeMap, reflectDir).rgb, 1.0f);
	color = vec4(rim, 1.0f) + vec4(texture(cubeMap, reflectDir).rgb, 1.0f);
}