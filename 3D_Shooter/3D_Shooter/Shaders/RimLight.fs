#version 450 core

in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoord;

out vec4 color;

uniform sampler2D tex;
uniform float ambientStr = 0.5f;
uniform vec3 ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
uniform vec3 lightPos = glm::vec3(0.0f, 5.0f, 0.0f);
uniform float lightSpecStr = 0.5f;
uniform vec3 camPos;
uniform float shininess = 16.0f;
uniform vec3 rimColor = glm::vec3(1.0f, 0.0f, 0.0f);

void main()
{
	// Ambient Light
	vec3 ambient = ambientStr * ambientColor;

	// Light Direction
	vec3 norm = normalize(fragNormal);
	vec3 lightDir = normalize(fragPos - lightPos);

	// Diffuse Coloring
	float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStr * lightColor;

	// Specular Highlight
	vec3 negViewDir = normalize(camPos - fragPos);
	vec3 halfwayVec = normalize(-lightDir + negViewDir);
	float spec = pow(max(dot(norm, halfwayVec), 0.0f), shininess);
	vec3 specular = lightSpecStr * spec * lightColor;

	// Rim Lighting
	float rimFactor = 1.0 - dot(norm, negViewDir);
	rimFactor = smoothstep(0.0, 1.0, rimFactor);
	rimFactor = pow(rimFactor, 1);
	vec3 rim = rimFactor * rimColor * lightColor;

	color = vec4(ambient + diffuse + specular + rim, 1.0f) * texture(tex, fragTexCoord);
}