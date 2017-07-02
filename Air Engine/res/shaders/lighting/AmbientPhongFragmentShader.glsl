#version 330 core

struct Material {
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular1;
	sampler2D texture_specular2;

	vec3 specular;
	float shininess;
};

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;

in vec4 out_Color;
in vec2 out_TexCoord;
in vec3 out_Normal;
in vec3 out_FragPos;

out vec4 color;

void main() {
	vec3 lightColor = vec3(1.0, 1.0, 1.0);
	//color = out_Color;

	vec3 normal = normalize(out_Normal);
	vec3 lightDir = normalize(lightPos - out_FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * vec3(texture(material.texture_diffuse1, out_TexCoord)) * lightColor;

	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - out_FragPos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = spec * vec3(texture(material.texture_specular1, out_TexCoord)) * lightColor;

	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * vec3(texture(material.texture_diffuse1, out_TexCoord)) * lightColor;
	vec3 result = /*texture(texture_diffuse1, out_TexCoord).xyz **/ (ambient + diffuse + specular);
	color = vec4(result, 1.0);
}
